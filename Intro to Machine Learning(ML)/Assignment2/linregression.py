import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import PolynomialFeatures
from sklearn.metrics import mean_absolute_error

accuracy_list = []

xtrain = pd.read_csv("xTrain.csv")
ytrain = pd.read_csv("yTrain.csv")
xtest = pd.read_csv("xTest.csv")
#Scale xtrain
scaler = MinMaxScaler()
xtrain = pd.DataFrame(scaler.fit_transform(xtrain), columns=xtrain.columns)
ytrain = pd.DataFrame(scaler.fit_transform(ytrain), columns=ytrain.columns)
xtest = pd.DataFrame(scaler.fit_transform(xtest), columns=xtest.columns)
scaler.fit_transform(ytrain)

#This drops any and all values where the most common element appears more than 90%
#of the time as this information probably isn't the most useful.

labels = list(xtrain.columns.values)
for elem in labels:
    ##If 90% (.9) or more of a column have the same value.
    #then the column will be dropped. This value can be changed if needed.
    if (list(xtrain[elem].value_counts(normalize = True))[0]) > 0.98:
        xtrain.drop(columns = elem, inplace=True)
        xtest.drop(columns = elem, inplace=True)

# transform data
poly = PolynomialFeatures(2)
xtrain = poly.fit_transform(xtrain)
xtest = poly.fit_transform(xtest)


#randomly select 1/5th of the data
indexes = np.random.randint(low=0, high=xtrain.shape[0], size=30000)
xstoch = np.take(xtrain,indexes,0)
ystoch = np.take(ytrain,indexes,0)

#w = np.linalg.pinv(xstoch).dot(ystoch)
w = xstoch.T.dot(xstoch)

#simulate identity matrix regularization (not enough memory for full)
# (Xt*X - gamma*I) but with a 0 in the top left corner of the matrix
gamma = 0.2
for i in range(1, w.shape[0]):
    w[i,i] += gamma
   
#linear regression closed form with regularization
w = np.linalg.inv(w).dot(xtrain.T.dot(ytrain))

#learning rate
l_rate = 0.01

#create list of all indexes
indexes = np.arange(0, xtrain.shape[0])
np.random.shuffle(indexes)

steps = 20000
epochs = 2
for i in range(epochs):

    #repeat until epoch is over
    index = 0
    while ((indexes.shape[0] - index) > steps):
        #select a number(steps) random entries from the index list and access them
        xstoch = np.take(xtrain,indexes[index:index+steps],0)
        ystoch = np.take(ytrain,indexes[index:index+steps],0)
       
        #perform gradient descent calculation
        grad = 2 * (xstoch.T.dot(xstoch.dot(w)-ystoch) / xstoch.shape[0])
        w = w - l_rate * grad
       
        #increment search space
        index+=steps
       
    #when the epoch finishes, reset the index list
    indexes = np.arange(0, xtrain.shape[0])
    np.random.shuffle(indexes)
    l_rate-=0.0001
    ypred = xtrain.dot(w)
    accuracy_list.append(mean_absolute_error(ytrain,ypred))

import xlsxwriter 
row = 1
output = xtest.dot(w)
print(output)
workbook = xlsxwriter.Workbook('output.xlsx') 
worksheet = workbook.add_worksheet()  
worksheet.write(0, 0, 'Index')
worksheet.write(0, 1, 'Label') 
for i in range(len(xtest)):
    worksheet.write(row, 0, i)
    worksheet.write(row, 1, output[i])
    row += 1

workbook.close()
