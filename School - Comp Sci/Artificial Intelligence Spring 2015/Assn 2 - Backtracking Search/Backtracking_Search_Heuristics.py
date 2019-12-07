__author__ = 'ashley'

import copy
import operator
from Node import Node


class Backtracking_Search_Heuristics:


    def chooseNextVariable(self, csp):
	"""
	    the point of this function is to choose the next variable to be assigned.  Why do we need to choose the variables in a particular order?  Technically, we could brute force this and just crunch
	    out all possible combinations of variable assignments, and then check each one against the constraints, but we have some heuristics to help us avoid computing variable assignment combinations
	    of lesser "quality". By assigning variables of higher "quality" first, we reduce branching higher in the search and thus reduce problem complexity considerably.

	    In order to choose the next variable, our first choice is the variable with the least number of values in it's domain.
	     If there are ties, our second choice is the variable with with the highest degree.
	     The degree of a variable is the number of a constraints on it.
	     As a last resort if there are still ties, we will make the arbitrary choice of the variable that is lowest alphabetically.
	     This arbitrary is not that significant since the variables have little difference in "quality"

	     One heuristic for measuring the relative quality of a variable concerning whether its assignment should be computed first is the number of values in it's domain.
	     If we assign varianles with the smallest domains first, we reduce branching at the top of the search tree, thus reducing problem complexity considerably.
	    Another heuristic for measuring the quality of a variable is to count the number of constraints on that variable.  A variable with more constraints on it will have fewer valid
	    assinments and thus assigning it higher in the search tree (earlier in the problem solution) will reduce branching and problem complexity as well.
	    This is often used as a tie breaker after the number of values heuristic.

	    :param csp: the current state of the constraint satisfaction problem
	    :return: the next variable to be assigned
	    """

        # first we need to find the variable with the least number of values in its domain
		# One heuristic for measuring the relative quality of a variable concerning whether its assignment should be computed first is the number of values in it's domain.
	    # If we assign varianles with the smallest domains first, we reduce branching at the top of the search tree, thus reducing problem complexity considerably.
        minimumNumberOfValues = 999
        for var in csp.variables:
            if len(var.domain) < minimumNumberOfValues:
                minimumNumberOfValues = len(var.domain)

        # now we need to know if there are any ties for minimum number of values. If there is a tie we will break the tie using the degree heuristic
        numValTies = []
        for var in csp.variables:
            if len(var.domain) == minimumNumberOfValues:
                numValTies.append(var)

        # if there are no ties we simply return the variable with the least number of values
        if len(numValTies) == 1:
            return numValTies.pop(0)
        else:
            # but otherwise we have to deal with the ties

            # we use the degree heuristic to break this tie.
            # the degree of a variable is the number of constraints on it.
            # a vsriable with more constraints will have a higher degree
            greatestDegree = 0
            for var in csp.variables:
                if var.degree > greatestDegree:
                    greatestDegree = var.degree

            # now we need to see if there are any ties, ie, variables of equal degree
            degreeTies = []
            for var in csp.variables:
                if var.degree == greatestDegree:
                    degreeTies.append(var)

            # if there are no ties we return the var with highest degree
            if len(degreeTies) == 1:
                return degreeTies.pop(0)
            else:
                # if there are ties then we return the variable that is the lowest alphabetically
                lowestAlpha = 'Z'
                for dties in degreeTies:
                    if dties.name < lowestAlpha:
                        lowestAlpha = dties.name

                for dties in degreeTies:
                    if dties.name is lowestAlpha:
                        return dties

    def getOrderedValues(self, currentVariable, currentNode):
        """generates the children of the current node.  The children will be placed in order of importantance from left to right"""

        # edge case : only one value
        if len(currentVariable.domain) == 1:
            return currentVariable.domain.pop(0)

        # a dictionary holding the num affected values for each value assignment
        # For example, if no variables are allowed to have the same value, if I assign a value to one variable, it will affect the domains of all the other variables because they can't use it now.
        valueEffectDict = {}
        constraintsWithVar = self.getConstraintsWithVar(currentVariable, currentNode.currentcsp)

		# Here we are basically creating a dictionary of the number of values (including the values of other variables) affected by an assignment of the current value.
        for val in currentVariable.domain:
            for con in constraintsWithVar:
                for var in currentNode.currentcsp.variables:
                    for dval in var.domain:
                        # print val + con.operator + dval + " is " + str(con.ops[con.operator](val, dval))
                        if con.ops[con.operator](val, dval) is False:
                            if valueEffectDict.get(val) is None:
                                valueEffectDict[val] = 1
                            else:
                                valueEffectDict[val] = int(valueEffectDict.get(val) + 1)

        # sort the values by num effects on other values and then makes nodes out of them
        sortedVarValuesTuples = sorted(valueEffectDict.items(), key=operator.itemgetter(1))

        print "value effects: " + str(sortedVarValuesTuples)

        # now let's make a list of just the values in the proper order
        sortedVals = []
        for tuple in sortedVarValuesTuples:
             sortedVals.append(tuple[0])

        return sortedVals

    def createChildNodes(self, sortedVarValues, currentNode, currentVariable):
        newChildren = []

        for value in sortedVarValues:
            # make new node and set currentNode as the parent
            newChild = Node(currentNode)

            # grab the assignment from the parent node
            newChild.assignment = copy.deepcopy(currentNode.assignment)
            # newChild.printAssignment()
            newChild.currentcsp = copy.deepcopy(currentNode.currentcsp)

            # grab the value we wanted to change and put it in the assignment of the new child
            newChild.assignment[currentVariable.name] = value

            # add the child to the list, we will use this list later
            newChildren.append(copy.deepcopy(newChild))

        # now that we've made all the children, set their parent nodes, and altered their assignment
        # with the proper value, now we're gonna set all their right sibling pointers
        #basically, this pointer makes printing the tree easier
        i = 1
        for child in newChildren:
           child.rightSibling = newChildren[i]
           if i is len(newChildren):
               child.rightSibling is None

        currentNode.children = newChildren

        return newChildren

    def getConstraintsWithVar(self, currentVariable, csp):
        # print "get cons"
        constraintsWithVar = []

        for con in csp.constraints:
            if con.var1 == currentVariable.name or con.var2 == currentVariable.name:
                constraintsWithVar.append(con)

        # now, we need to make sure that in all constraints involving this variable that the var in question is
        # on the left
        for con in constraintsWithVar:
            if con.var1 != currentVariable.name and con.operator is '>':
            #    print "swap >"
                tempvar = con.var1
                con.var1 = con.var2
                con.var2 = tempvar
                con.operator = '<'
            if con.var1 != currentVariable.name and con.operator is '<':
            #    print "swap <"
                tempvar = con.var1
                con.var1 = con.var2
                con.var2 = tempvar
                con.operator = '>'
            if con.var1 != currentVariable.name:
             #   print "plain swap"
                tempvar = con.var1
                con.var1 = con.var2
                con.var2 = tempvar
            print con.var1 + con.operator + con.var2

            #print "cons with " + currentVariable.name
            #for con in constraintsWithVar:
            #    print con.var1 + con.operator + con.var2
        return constraintsWithVar

