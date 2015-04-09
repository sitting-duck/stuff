__author__ = 'ashley'

import copy
from Variable import Variable
from Clause import Clause

# this function is going to grab the initial knowledge base from a file given from the command line.
# the initial knowledge base is just a set of clauses. A clause is basically a statement, so our knowledge base is
# essentially a collection of statements.  The knowledge base is the set of stuff that is known. You can also see the
# Clause class to get more of an idea of what's in a clause.
def getClausesFromFile(KBFileName):

    # container for the clauses we are going to grab
    clauses = []

    #each clause will be given a number to help keep track of it
    clauseNumber = 0

    KBFile = open(KBFileName)
    lines = KBFile.readlines()

    #for every line in the file make a new clause
    for line in lines:

        clauseNumber += 1

        # tokenize the line
        tokens = line.split()

        # for every token in line make a new variable. A clause is made up of these variables.
        variables = []
        for token in tokens:

            #see if there is a ~ for this variable
            neg = False
            name = ""
            if token[0] == '~':
                neg = True
                name = token.replace("~", "")
            else:
                name = token

            newVar = Variable(name, neg)

            variables.append(copy.deepcopy(newVar))
            # end token loop

        # now take that list of variables and use it to make a clause.  Clauses are numbered sequentially in the
        # order they are made/listed in the knowledge base file
        newClause = Clause(clauseNumber, variables)

        clauses.append(copy.deepcopy(newClause))
        #end line loop

    return clauses