__author__ = 'ashley'


import operator
import copy
from Node import Node
from Backtracking_Search_Heuristics import Backtracking_Search_Heuristics
import sys

class Backtracking_Search:

    def __init__(self, cspArg, forwardCheckingArg):

        # the csp problem we are trying to solve
        self.csp = copy.deepcopy(cspArg)

        # a root node for our 'tree'. The root nodes' parent is 'none', that's how we know it's the root
        self.root = Node()

        # currentNode is initially set to root and we will generate the tree as we go along searching
        self.currentNode = self.root
        self.currentNode.currentcsp = copy.deepcopy(cspArg)

        # we initially start with the entire set of variables, but remove them and add them back depending on where we
        #  are in the search.as we go down the tree, we eliminate variables, if we backtrack back up the tree, we add
        # them back
        self.remainingVariables = self.csp.variables

        self.bsh = Backtracking_Search_Heuristics()

        if forwardCheckingArg == "none":
            self.forwardChecking = False
        else:
            self.forwardChecking = True

    def backtrack(self, currentNode):

        # if the assignment of the current node is valid then we return it as the solution
        if self.csp.isCompleteAndValid(self.currentNode.assignment):
            return self.currentNode.assignment

        # let's select the next variable that we want to test the values for
        if len(currentNode.currentcsp.variables) is 0:
            return False
        else:
            currentVariable = self.bsh.chooseNextVariable(currentNode.currentcsp)

        # and remove it from the list of available variables
        currentNode.currentcsp.variables.remove(currentVariable)

        # get the values from this variables domain and put them in the order that we want to test them
        sortedVarValues = self.bsh.getOrderedValues(currentVariable, self.currentNode)
        newChildren = self.bsh.createChildNodes(sortedVarValues, currentNode, currentVariable, self.forwardChecking)

        for child in newChildren:
            #print "current child assn: " + str(child.assignment)
            if self.csp.isCompleteAndValid(child.assignment):
                child.printAssignment()
                print "solution"
                sys.exit()
                #print "finished with : "
                #child.printAssignment
                return True


            currentNode = child
            currentNode.printAssignment()
            print " failure"
            result = self.backtrack(currentNode)

        return False

    #for some reason after we eliminate all the vars we are not backtracking back upward







