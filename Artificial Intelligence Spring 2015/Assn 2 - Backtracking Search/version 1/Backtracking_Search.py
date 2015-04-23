__author__ = 'ashley'

from Node import Node

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

        minimumRemainingValues = 999

        # find the minimum num of values for any variable.  We want to choose the variable with the least number
        #  of values in order to reduce branching on the tree
        for var in self.csp.variables:
            if len(var.domain) < minimumRemainingValues:
                minimumRemainingValues = len(var.domain)

        print "num min rem vals was : " + str(minimumRemainingValues)

        # now we need to check for ties.
        ties = []
        for var in self.csp.variables:
            if len(var.domain) == minimumRemainingValues:
                ties.append(var)

        # if there is more than one var in the ties list, then we know that we have a tie,
        # in the case of a tie we apply the "degree heuristic" aka the "most constraining variable heuristic
        # if there is a tie after comparing using the degree heuristic then we will break ties alphabetically
        print "ties were "
        for tie in ties:
            print tie.name

        # the degree heuristic basically just counts the number of times a var shows up in the constraints
        degree = []
        if len(ties) == 1:
            return ties[0]
        else:
            for con in self.csp.constraints:

                print "print the damn vars"
                for var in self.csp.variables:
                    print var.name

                print "the index thing " + self.csp.variables.index(con.var1)

                for
                degree[self.csp.variables.index(con.var1)] += 1
                degree[self.csp.variables.index(con.var2)] += 1

            #print out degrees
            print "degrees"
            for deg in degree:
                print deg

            # let's do a check here to make sure the degree list looks right
            # now that we know the degree for each variable, let's find the ones with the highest degree
            highestDegree = 0
            for varDegree in degree:
                if varDegree > highestDegree:
                    highestDegree = varDegree

            # now we check to see if there are any ties, this time the ties indicate the two vars have the same degree
            degreeTies = []
            for varDegree in degree:
                if varDegree == highestDegree:
                    degreeTies.append(varDegree)

            # if there is more than one in the degreeTies list, then we have a tie
            if len(degreeTies) == 1:
                return degreeTies[0]
            # if again we have ties, then we break ties alphabetically
            else:
                degreeTiesAlpha = []
                i = 0
                for varDegree in degree:
                    if varDegree == highestDegree:
                        degreeTiesAlpha.append(csp.variables.get(i).name)
                        i += 1
                degreeTiesAlpha.sort()
                return degreeTiesAlpha.pop(0)

