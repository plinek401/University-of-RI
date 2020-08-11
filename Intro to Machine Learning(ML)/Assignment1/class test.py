import sys
import math
import pandas as pd

class Node():
	def __init__(self, attribute, threshold):
		self.attr = attribute
		self.thres = threshold
		self.left = None
		self.right = None
		self.leaf = False
		self.predict = None

# First select the threshold of the attribute to split set of test data on
# The threshold chosen splits the test data such that information gain is maximized
def select_threshold(df, attribute, predict_attr):
        values = df[attribute].tolist()
	# Remove duplicate values by converting the list to a set, then sort the set
        values = set(values)
        values = list(values)
        values.sort()
        max_ig = -10000
        thres_val = 0
        # try all threshold values that are half-way between successive values in this sorted list
        for i in range(0, len(values) - 1):
                thres = (values[i] + values[i+1])/2
                ig, part1, part2 = info_gain(df, attribute, predict_attr, thres)
                if ig > max_ig:
                	max_ig = ig
                	thres_val = thres
                	topPart = part1
                	bottomPart = part2
        # Return the threshold value that maximizes information gained
        return thres_val, topPart, bottomPart

# Calculate info content (entropy) of the test data
def info_entropy(df, predict_attr):
        # Dataframe and number of positive/negatives examples in the data
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
        
        # Calculate entropy
        total = one+two+three+four+five
        if one == 0 or two == 0 or three == 0 or four == 0 or five == 0:
        	I = 0
        else:
        	I = ((-1*one)/(total))*math.log(one/(total), 5) + ((-1*two)/(total))*math.log(two/(total), 5) + ((-1*three)/(total))*math.log(three/(total), 5) + ((-1*four)/(total))*math.log(four/(total), 5) + ((-1*four)/(total))*math.log(four/(total), 5)
        return I

# Calculates the weighted average of the entropy after an attribute test
def remainder(df, df_subsets, predict_attr):
        # number of test data
        num_data = df.shape[0]
        remainder = float(0)
        for df_sub in df_subsets:
        	if df_sub.shape[0] > 1:
        		remainder += float(df_sub.shape[0]/num_data)*info_entropy(df_sub, predict_attr)
        return remainder

# Calculates the information gain from the attribute test based on a given threshold
# Note: thresholds can change for the same attribute over time
def info_gain(df, attribute, predict_attr, threshold):
        sub_1 = df[df[attribute] < threshold]
        sub_2 = df[df[attribute] > threshold]
        # Determine information content, and subract remainder of attributes from it
        ig = info_entropy(df, predict_attr) - remainder(df, [sub_1, sub_2], predict_attr)
        return ig, sub_1, sub_2

# Returns the number of positive and negative data
def num_class(df, predict_attr):
        print("num_class was called!")
        p_df = df[df[predict_attr] == 1]
        n_df = df[df[predict_attr] == 0]
        return p_df.shape[0], n_df.shape[0]

# Chooses the attribute and its threshold with the highest info gain
# from the set of attributes
def choose_attr(df, attributes, predict_attr):
        print("choose_attr was called!")
        max_info_gain = -100000
        best_attr = None
        threshold = 0
        # Test each attribute (note attributes maybe be chosen more than once)
        for attr in attributes:
        	thres, topPart, bottomPart = select_threshold(df, attr, predict_attr)
        	ig, temp, temp2 = info_gain(df, attr, predict_attr, thres)
        	if ig > max_info_gain:
        		max_info_gain = ig
        		best_attr = attr
        		threshold = thres
        return max_info_gain, best_attr, threshold, topPart, bottomPart

# Builds the Decision Tree based on training data, attributes to train on,
# and a prediction attribute
def build_tree(df, cols, predict_attr):
        print("build_tree was called!")
        # Get the number of positive and negative examples in the training data
        p, n = num_class(df, predict_attr)
        # If train data has all positive or all negative values
        # then we have reached the end of our tree
        if p == 0 or n == 0:
        	# Create a leaf node indicating it's prediction
        	leaf = Node(None,None)
        	leaf.leaf = True
        	if p > n:
        		leaf.predict = 1
        	else:
        		leaf.predict = 0
        	return leaf
        else:
        	# Determine attribute and its threshold value with the highest
        	# information gain
        	best_attr, threshold = choose_attr(df, cols, predict_attr)
        	# Create internal tree node based on attribute and it's threshold
        	tree = Node(best_attr, threshold)
        	sub_1 = df[df[best_attr] < threshold]
        	sub_2 = df[df[best_attr] > threshold]
        	# Recursively build left and right subtree
        	tree.left = build_tree(sub_1, cols, predict_attr)
        	tree.right = build_tree(sub_2, cols, predict_attr)
        	return tree

# Given a instance of a training data, make a prediction of healthy or colic
# based on the Decision Tree
# Assumes all data has been cleaned (i.e. no NULL data)
def predict(node, row_df):
        print("predict was called!")
        # If we are at a leaf node, return the prediction of the leaf node
        if node.leaf:
        	return node.predict
        # Traverse left or right subtree based on instance's data
        if row_df[node.attr] <= node.thres:
        	return predict(node.left, row_df)
        elif row_df[node.attr] > node.thres:
        	return predict(node.right, row_df)

# Given a set of data, make a prediction for each instance using the Decision Tree
def test_predictions(root, df):
        print("Test_prediction was called!")
        num_data = df.shape[0]
        num_correct = 0
        for index,row in df.iterrows():
        	prediction = predict(root, row)
        	if prediction == row['y']:
        		num_correct += 1
        return round(num_correct/num_data, 2)

# Prints the tree level starting at given level


def main():
	# An example use of 'build_tree' and 'predict'
	df_train = pd.read_csv('xTrain.csv')
	y = pd.read_csv('yTrain.csv')
	attributes =  list(df_train.columns.values)
	df_train['y'] = y['y']
	df_train=df_train[ :50]
	#root = build_tree(df_train, attributes, df_train['y'])
        
	infoGain, bestAttribute, threshold, topPart, bottomPart = choose_attr(df_train, attributes, 'y')
	print(infoGain, bestAttribute, threshold)

if __name__ == '__main__':
	main()
