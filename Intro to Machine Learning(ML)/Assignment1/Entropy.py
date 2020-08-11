import math #Entropy
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import statsmodels.api as sm


#----------------------------------------Globals-----------------------------------------------------------
LEVELS_OF_TREE = 5

#--------------------------------------------------------------
#----------------------------------------Classes-----------------------------------------------------------------
class Node:
    def __init__(self, name, val):
        self.name = name #feature
        self.boundaryVal = val
        self.left = None
        self.right = None

    def insert(self, name, boundary):
        print("")


    def preorder(self):
        if self:
            print(self.value)
            if self.left:
                self.left.prorder()
            if self.right:
                self.right.preorder()
                
class DecisionTree:
    def __init__(self):
        self.root = None

    def insert(self, name, val):
        if self.root:
            return self.root.insert(name, val)
        else:
            self.root = Node(name, val)
            return True

    def preorder(self):
        print("Preorder")
        self.root.preorder()

#----------------------------------------------------------------------        
#-----------------------------------Entropy and Info Gain Functions------------------------------------------------

def informationGain(data, labels):
    rows = data.shape[0]
    infoGain = 0 #Tracks the maximum Information Gain
    cols = len(labels) #For ease of use, stores the number of columns.
    baseEntropy = calcEntropy(data[labels[cols-1]])#Stores the entropy of current data set("node")
    #This loop loops through each column
    for i in range(cols):
        #Elements stores each element in the column. Counts stores the count each element appears. 
        elements, counts = np.unique(data[labels[i]], return_counts=True)
        gain = 0
        #For each column, this loops through each unique element
        for elem in range(len(elements)):
            grouped = data.groupby(labels[i]) #Groups the dataframe by each element in column.
            temp = grouped.get_group(elements[elem]) #Stores the current group by each element.
            ent = calcEntropy(temp[labels[cols-1]]) #stores entropy calculation
            gain = gain + (counts[elem]/rows)*ent
        if((1-gain) > infoGain):
            infoGain = (1-gain)
            trackColName = labels[i]
            
    return trackColName

def calcEntropy(column):
    column = list(column)
    entropy = 0
    total = len(column)
    elements, counts = np.unique(column, return_counts=True)
    numElems = len(elements)
            
    for elem in range(len(counts)):
        pi = counts[elem]/total
        if(numElems < 2):
            entropy = entropy - pi*(math.log(pi,2))
        else:
            entropy = entropy - pi*(math.log(pi, numElems))

    return entropy

#-------------------------------------------------------------
#--------------------------------Some Statistical Operations---------------------------------------------
def qqplot(data, counts):
    mod_fit = sm.OLS(data, counts).fit()
    res = mod_fit.resid # residuals
    fig = sm.qqplot(res, line='s')
    plt.show()

def removeOutliers(elements, counts):
    newElems = []
    newCounts = []
    for i in range(len(elements)):
        if(elements[i] <= 1000 and elements[i] >= -1000):
            newElems.append(elements[i])
            newCounts.append(counts[i])
    newElems = np.array(newElems)
    newCounts = np.array(newCounts)

    return newElems, newCounts
    
    
def visualize(data):
    elements, counts = np.unique(data['X177'], return_counts=True)

    print("Elements:")
    print("Shape:",elements.shape)
    print("Minimum:",np.min(elements))
    print("Maximum:",np.max(elements))
    print("Mean:",np.mean(elements))
    print("\n----------------\n")
    
    print("Count:")
    print("Shape:",counts.shape)
    print("Minimum:",np.min(counts))
    print("Maximum:",np.max(counts))
    print("Mean:",np.mean(counts))

    #qq-plot
    elements, counts = removeOutliers(elements, counts)
    qqplot(elements, counts)

    #Distribution
##    plt.rcParams["figure.figsize"] = (10, 10)
##    fig, ax = plt.subplots()
##    ax.bar(elements,counts, color ="blue")
##    ax.set(title="Elements Occurance of Column 'X100'")
##    ax.set(xlabel="Elements", ylabel="Occurance");
##    plt.show()

#-------------------------------------------------------------------------------
#-------------------------------Main Function---------------------------------------------------    
def main():
    #data = pd.read_csv("xtrain.csv")
    data = {'Outlook' :    [0,0,1,2,2,2,1,0,0,2,0,1,1,2],
            'Temperature': [0,0,0,1,2,2,2,1,2,1,1,1,0,1],
            'Wind' :       [1,2,1,1,1,2,2,1,1,1,2,2,1,2],
            'Humidity':    [1,1,1,1,2,2,2,1,2,2,2,1,2,1]}
    output = {'PlayTennis':[1,1,2,2,2,1,2,1,2,2,2,2,2,1]}
            
    data = pd.DataFrame(data)
    output = pd.DataFrame(output)
    
    labels = list(data.columns.values)

    #visualize(data)
    
    colName = informationGain(data, labels)
    
    print("{} should be the split".format(colName))


main()
#---------------------------------------------------------------------------

