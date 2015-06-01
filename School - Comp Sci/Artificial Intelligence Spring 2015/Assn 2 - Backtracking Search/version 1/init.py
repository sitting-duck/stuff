__author__ = 'ashley'

from Variable import Variable
from Constraint import Constraint

def getVariablesFromFile(varFileName):

    variables = []

    varFile = open(varFileName)

    # parse the varFile. In this file on each line is a variable.
    # at the beginning of the line is a single letter variable name, followed by a colon and its possible space separated
    # values, each of which is an integer
    lines = varFile.readlines()

    for line in lines:
        # tokenize the line
        tokens = line.split()

        # the first token is going to be the letter name of the variable
        varName = tokens.pop(0) #grab the first token
        varName = varName[:-1]  #get rid of that pesky colon

        # with the name popped off the rest of the list is all the possible int values for that variable, ie the domain
        domain = tokens

        # now let's take that stuff we just extracted from the line and make a variable out of it
        variable = Variable(varName, domain)
        #print "got varname " + variable.varName

        #add that variable to the list
        variables.append(variable)

    varFile.close()

    return variables

def getConstraintsFromFile(constraintFileName):

    constraints = []

    constraintFile = open(constraintFileName)

    #parse the constraint file. Each line is a new constraint, for example A = B, or B > C
    lines = constraintFile.readlines()

    for line in lines:
        #tokenize the line
        tokens = line.split()

        #grab the first token, it's a variable name
        var1 = tokens.pop(0)

        #grab the second token, it's an operator =, !, >, or <
        operator = tokens.pop(0)

        #grab the last token, it's another variable name
        var2 = tokens.pop(0)

        #now let's take that stuff we just extracted from the line and make a constraint out of it
        constraint = Constraint(var1, operator, var2)

        #add that constraint to the list
        constraints.append(constraint)

    constraintFile.close()

    return constraints