__author__ = 'ashley'

import copy
import operator
from Node import Node


class Backtracking_Search_Heuristics:

    def chooseNextVariable(self, csp):

        # first we need to find the least num values
        minNumVal = 999
        for var in csp.variables:
            if len(var.domain) < minNumVal:
                minNumVal = len(var.domain)

        # now we need to know if there are any ties.
        numValTies = []
        for var in csp.variables:
            if len(var.domain) == minNumVal:
                numValTies.append(var)

        # if there is no tie we return
        if len(numValTies) == 1:
            return numValTies.pop(0)
        else:
            # but otherwise we have to deal with the ties

            # we use the degree heuristic to break this tie
            greatestDegree = 0
            for var in csp.variables:
                if var.degree > greatestDegree:
                    greatestDegree = var.degree

            # now we need to see if there are any ties
            degreeTies = []
            for var in csp.variables:
                if var.degree == greatestDegree:
                    degreeTies.append(var)

            # if there is no tie we return the var with highest degree
            if len(degreeTies) == 1:
                return degreeTies.pop(0)
            else:
                # in this case we are going to break ties alphabetically
                lowestAlpha = 'Z'
                for dties in degreeTies:
                    if dties.name < lowestAlpha:
                        lowestAlpha = dties.name

                for dties in degreeTies:
                    if dties.name is lowestAlpha:
                        return dties

    def getOrderedValues(self, currentVariable, currentNode):
         #now we're going to generate the next level of the tree

        # edge case : only one value
        if len(currentVariable.domain) == 1:
            return currentVariable.domain.pop(0)

        # a dictionary holding the num affected values for each value assignment
        valueEffectDict = {}

        constraintsWithVar = []
        constraintsWithVar = self.getConstraintsWithVar(currentVariable, currentNode.currentcsp)
        # for con in constraintsContainingCurrentVariable:
        #     print con.var1 + con.operator + con.var2

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

        # now let's sort the values by num effects on other values and then makes nodes out of them
        sortedVarValuesTuples = sorted(valueEffectDict.items(), key=operator.itemgetter(1))

        #print "value effects: " + str(sortedVarValuesTuples)

        # now let's make a list of just the values in the proper order
        sortedVals = []
        for tuple in sortedVarValuesTuples:
             sortedVals.append(tuple[0])

        return sortedVals

    def createChildNodes(self, sortedVarValues, currentNode, currentVariable, forwardChecking):
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

            #forward checking step
            if(forwardChecking):
                    for con in newChildren[-1].currentcsp.constraints:
                       #print con.var1 + con.operator + con.var2
                       for otherVar in newChildren[-1].currentcsp.variables:
                            tempDomain = copy.deepcopy(otherVar.domain)
                            if con.operator == '!':
                                if otherVar.domain.contains(value):
                                    tempDomain.remove(value)
                            if con.operator == '=':
                                for otherVal in otherVar.domain:
                                    if otherVal != value:
                                        tempDomain.remove(otherVal)
                            if con.operator == '>':
                                for otherVal in otherVar.domain:
                                    if otherVal >= value:
                                        tempDomain.remove(otherVal)
                            if con.operator == '<':
                                for otherVal in otherVar.domain:
                                    if otherVal <= value:
                                        tempDomain.remove(otherVal)
                            otherVar.domain = copy.deepcopy(tempDomain)
                           # print "current var: " + currentVariable.name + value + " child var: + " + otherVar.name + (str(otherVar.domain))



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
            #print con.var1 + con.operator + con.var2

            #print "cons with " + currentVariable.name
            #for con in constraintsWithVar:
            #    print con.var1 + con.operator + con.var2
        return constraintsWithVar

