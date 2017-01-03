#	INTRODUCTION    

In this code, the goal is to give gifts to children in such a way that each child receives as many gifts as they have put into a pool with minimal loss of desire. That is, the algorithim minimizes the likelihood that the child will receive an undesired gift. 

#	HOW TO COMPILE
The program is written in c++. In order to compile the program, type "make". 
To run the program type ./swapathon  

#	ALGORITHM

My algorithm is a branch and bound of sorts. The algorithm splits each of the children up into separate "children" into a gifting matrix, so that each "child" will receive only one gift. 

From there, a ranking matrix is generated. Each matrix at that level greedily chooses the best option. Supposing n children chose the same option, then the relaxed gift at that spot in the matrix is divied between the n children n times, so that each has 1/n of that particular gift. 

Of all the children, the ones which have the most minimal split (i.e. the lowest 1/n value), I choose to split on that particular value. 

On the split, that option is chosen, and all other ranks are set to an aribtrarily high point. 

If there are no splits, then the incumbent solution is set, and we return, then removing the branch. 

If any branch has a greater fitness than the incumbent, then we can also prune that branch. 

# OPTIMALITY

This program guarantees optimality due to its depth first nature, it finds a solution, and counts that as its best. It then prunes trees based off of that incumbent score. If the relaxed scores are worse than the incumbent, the tree is pruned. Otherwise, the tree continues branching. 

When it finds a better solution, that becomes the incumbent. The more incumbents we can get, the more we can prune until we get to our best option. 
 
# KNOWN ISSUES
The algorithm has, at least in retrospect, a potentially fatal flaw (i.e It is possible that a non optimal solution could occur, given that the optimal solution includes the first child having no ranked 1 gift. However, when running the code on a small segment with 5 children and 9 gifts, it seems to run perfectly. 

The algorithm, otherwise,  works very well, at least on a handful of the given problems, however, it does not run past 17 gifts with 4 children. I believe it relies in some memory leak, however, I am not able to locate it. Equally, I am working on another algorithm, but wish to subtmit this first (The other algorithm is unfortunately not working). 

Note: In this version, I apparently uploaded an old copy. The program segfaults for some bizarre reason when writing to file. I've commented that code out. It still prints the answers to the terminal. I'll eventually track down that error. 
