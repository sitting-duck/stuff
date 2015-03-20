__author__ = 'ashley'

from Node import Node
from Variable import Variable

class Backtracking_Search:

    def __init__(self, cspArg):

        # the csp problem we are trying to solve
        self.csp = cspArg

        # a root node for our 'tree'. The root nodes' parent is 'none', that's how we know it's the root
        self.root = Node()

        # currentNode is initially set to root and we will generate the tree as we go along searching
        self.currentNode = self.root

        # we initially start with the entire set of variables, but remove them and add them back depending on where we
        #  are in the search.as we go down the tree, we eliminate variables, if we backtrack back up the tree, we add
        # them back
        self.remainingVariables = self.csp.variables

    def backtrack(self):

        # if the assignment of the current node is valid then we return it as the solution
        if self.csp.isCompleteAndValid(self.currentNode.assignment):
            return self.currentNode.assignment

        # let's select the next variable that we want to test the values for
        nextVariable = self.chooseNextVariable(self.csp)
        print "chose var: " + nextVariable.name

    def chooseNextVariable(self, csp):

        # first we need to find the least num values
        minNumVal = 999
        for var in self.csp.variables:
            if len(var.domain) < minNumVal:
                minNumVal = len(var.domain)

        # now we need to know if there are any ties.
        numValTies = []
        for var in self.csp.variables:
            if len(var.domain) == minNumVal:
                numValTies.append(var)

        # if there is no tie we return
        if len(numValTies) == 1:
            return numValTies.pop(0)
        else:
            # but otherwise we have to deal with the ties

            # we use the degree heuristic to break this tie
            greatestDegree = 0
            for var in self.csp.variables:
                if var.degree > greatestDegree:
                    greatestDegree = var.degree

            # now we need to see if there are any ties
            degreeTies = []
            for var in self.csp.variables:
                if var.degree == greatestDegree:
                    degreeTies.append(var)

            # if there is no tie we return the var with highest degree
            if len(degreeTies) == 1:
                return degreeTies.pop(0)
            else:
                # in this case we are going to break ties alphabetically
                degreeTies.sort(str.lower)
                return degreeTies.pop(0)



