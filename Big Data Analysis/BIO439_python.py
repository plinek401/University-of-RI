#Pawel Linek
#Python Assignment - Kmers

import pandas as pd
import sys

def count_kmers(sequence, k):
    """Counting Kmers"""
    endPos = k
    kmers = []
    for startPos in range(len(sequence)):
        kmers.append(sequence[startPos: endPos])
        endPos += 1
        if(endPos-1 == len(sequence)):
            break
    return kmers
#This prints the associated kmer count. Change the 6 to anything to see it on others.


def create_df(sequence): # Using an input Sequence I find the dataframe of kmers.
    """Creating Dataframe based on Sequence"""
    #This gets me the list of kmers
    data = []
    for i in range(1, len(sequence)+1):
        kmers = count_kmers(sequence, i)
        data.append([i, len(set(kmers)), len(kmers)])

    #This creates the Dataframe of k, observed, and possible    
    df = pd.DataFrame()
    for i in range(len(sequence)):
        row = pd.Series(data[i])
        row_to_df = pd.DataFrame([row])
        df = pd.concat([df,row_to_df], ignore_index=True)
        
    df.columns = ["k", "Observed Kmers", "Expected Kmers"]

    return df

#This prints the above table.
#ddd = create_df(sequence)
#print(ddd.to_string(index=False))

#Linguistic Complexity
def linguistic_complexity(df):
    """Calculating Linguistic Complexity"""
    return df["Observed Kmers"].sum()/df["Expected Kmers"].sum()


#print(linguistic_complexity(df))


def main():
    """Puts all the above functions together to output df and linguistic complexity"""
    #Read from command line
    with open(sys.argv[1], 'r') as f:
        sequence = f.read()
    print(sequence)

    #Create DataFrame
    df = create_df(sequence)
    print(df.to_string(index=False))

    #output linguistic complexity
    print(linguistic_complexity(df))
    
if __name__ == "__main__":
    main()
else: 
    print("Failed Execution")










    
