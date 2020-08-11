#Imports.
import sys
import math
import numpy as np
import pandas as pd
from openpyxl import Workbook


def get_threshold(df, values, attribute, outColName):
    
        max_infoGain = -10000
        thres_best = 0

        for i in range(len(values)-1):
            thresh = (values[i] + values[i+1])/2
            gain, part1, part2 = infoGain(df, attribute, outColName, thresh)
            if gain > max_infoGain:
                max_infoGain = gain
                thresh_best = thresh
                topPart = part1
                bottomPart = part2
        return thresh_best, topPart, bottomPart

# Calculate entropy of the test data
def entropy(df, predict_attr):
    # Find number of each label [1-5] 
    one_df = df[df[predict_attr] == 1]
    two_df = df[df[predict_attr] == 2]
    three_df = df[df[predict_attr] == 3]
    four_df = df[df[predict_attr] == 4]
    five_df = df[df[predict_attr] == 5]
    one = float(one_df.shape[0])
    two = float(two_df.shape[0])
    three = float(three_df.shape[0])
    four = float(four_df.shape[0])
    five = float(five_df.shape[0])
        
    # Calculate entropy, sets each individual label to 0 if none are present
    total = one+two+three+four+five
    if (one == 0):
        E1 = 0
    else:
        E1 = ((-1*one)/(total))*math.log(one/(total), 5)
    if (two == 0):
        E2 = 0
    else:
        E2 = ((-1*two)/(total))*math.log(two/(total), 5)
    if (three == 0):
        E3 = 0
    else:
        E3 = ((-1*three)/(total))*math.log(three/(total), 5)
    if (four == 0):
        E4 = 0
    else:
        E4 = ((-1*four)/(total))*math.log(four/(total), 5)
    if (five == 0):
        E5 = 0
    else:
        E5 = ((-1*five)/(total))*math.log(five/(total), 5)
    I = E1 + E2 + E3 + E4 + E5
    return I

# Helper function for entropy function. Calculates the weighted average
def entHelper(df, df_subsets, predict_attr):
    # number of test data
    num_data = df.shape[0]
    remain = float(0)
    for df_sub in df_subsets:
        if df_sub.shape[0] > 1:
            remain += float(df_sub.shape[0]/num_data)*entropy(df_sub, predict_attr)
        return remain

#Calc info gain based on the threshold we are currently looking at.
def infoGain(df, attribute, outColName, threshold):
    part1 = df[df[attribute] < threshold]
    part2 = df[df[attribute] > threshold]
        
    if (part1.shape[0] < 5) or (part2.shape[0] < 5):
        gain = 0
    else:
        gain = entropy(df, outColName) - entHelper(df, [part1, part2], outColName)
    return gain, part1, part2

#Finds the attribute which gets the best split. This calls get_threshold to find the threshold we should split on.
def get_attribute(df, attributes, outColName):
    max_info_gain = -100000
    threshold = 0
    # Test each attribute
    for att in attributes[:(len(attributes)-1)]:
        print(att, end="...")
        values = df[att].tolist()
        values = list(set(values))
        if (len(values) > 1):
            values.sort()
            if (len(values) > 50):
                values = values[(len(values)//4):((3*len(values))//4)]
            thres, topPart, bottomPart = get_threshold(df, values, att, outColName)
            gain, temp1, temp2 = infoGain(df, att, outColName, thres)
            if gain > max_info_gain:
                max_info_gain = gain
                best_attr = att
                threshold = thres
    print("")
    print("Selected Attribute ",best_attr)
    return max_info_gain, best_attr, threshold, topPart, bottomPart
    
#output our results into an excel sheet
def toExcel(outputs):
        workbook = Workbook()
        sheet = workbook.active
        for i in range(len(outputs)):
                index = "A" + str(i+1)
                output = "B" + str(i+1)
                sheet[index] = i
                sheet[output] = outputs[i]
        workbook.save(filename="Pawel and Jesse.xlsx")
    
    
###############################################################################

#DECISION TREE
#tree takes data set and prints a result
class DecisionTree:
    
    #initialize empty tree
    def __init__(self, D):
        attributes =  list(D.columns.values)
        self.head = self.GrowTree(0,D,attributes)
        
    #traverse takes a row and pushes it through the tree until a result is found
    def traverse(self, row):
        hold = self.head
        while (hold.branches != []):
            hold = hold.compare(row[hold.name])
        return hold.data[0]
    
    #classify takes a data set and attempts to find the best results
    def classify(self, D):
        results = []
        for row in range(D.shape[0]):
            x = D.iloc[row,:]
            results += [self.traverse(x)]
        return results
        
    #GROWTREE
    #takes a data set and a node, then creates a decision tree that fits the data
    def GrowTree(self, height, D, attributes):
        #max height is 20 to avoid overfitting
        max1 = 20
        
        #if homogenous, create Leaf
        elem = np.unique(D["y"])
        if (len(elem) == 1):
            return Node(data=self.majority(D),name="Leaf")
        
        #choose column and value to split data on
        gain,colname,split,D1,D2 = get_attribute(D, attributes, 'y')
        hold = Node(data=split, name=colname) 
        
                        
        #drop attribute so it doesn't get checked again
        attributes.remove(colname)
                        
        #establish left branch
        if ((D1.shape[0] > 19) and (height <= max1)):
            hold.branches += [self.GrowTree(height+1,D1,attributes)]
            
        #create leaf if very little data or max height reached
        else:
            hold.branches += [Node(data=self.majority(D1), name="Leaf")]
        
        #establish right branch
        if ((D2.shape[0] > 19) and (height <= max1)):
            hold.branches += [self.GrowTree(height+1,D2,attributes)]
            
        #create leaf if very little data or max height reached
        else:
            hold.branches += [Node(data=self.majority(D2), name="Leaf")]
            
        #return node
        return hold

                        
    def majority(self, D):
        elem, counts = np.unique(D["y"], return_counts=True)
        return elem[list(counts).index(max(counts))]
    
###############################################################################
#NODE
#takes a row of data and categorizes it
class Node:
    
        #initialize node
        def __init__(self, data=None, branch=None, name=None):
                self.name = name
                self.branches = []
                #if no branches, data is the return value
                #else each data point is a comparison value
                #     where if num < data[i], then branch[i]
                self.data = [data]
                
        #function to compare a num with stored comparison values and return a node
        def compare(self, num):
                if (num < self.data[0]):
                    return self.branches[0]
                #if num out of all ranges, return highest branch
                return self.branches[1]
                
                
###############################################################################

D = pd.read_csv('xTrain.csv')
E = pd.read_csv('yTrain.csv')
F = pd.read_csv('xTest.csv')
D['y'] = E.values
DT = DecisionTree(D[:1000])

print("Done Building Tree..")
results = DT.classify(F)
toExcel(results)


