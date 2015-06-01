
__author__ = 'ashley'

from Variable import Variable

class Clause:

    def __init__(self, numberArg = 0, varsArg = [], parentsArg = []):
        self.number  = numberArg
        self.vars = varsArg
        self.parents = parentsArg

    def __eq__(self, other):
        # note: this equality check does not check the clause numbers.  In the case that two equivalent clauses
        # have different clause numbers, they will still be technically equal if they have the same variables and
        # negations.  eg. p OR ~q is equal to ~p OR p
        return self.vars == other.vars and self.parents == other.parents


    def printClause(self):
        print str(self.number) + " ",
        for var in self.vars:
            var.printVariable()
            print " ",
        print "{",
        for parent in self.parents:
            print parent,
            if parent != self.parents[-1]:
                print ", ",
        print "}",

    def getClauseAsString(self):
        clause = str(self.number) + " "
        for var in self.vars:
            clause += var.getVariableAsString() + " "
        clause += "{"
        for parent in self.parents:
            clause += str(parent)
            if parent != self.parents[-1]:
                clause += ", "
        clause += "}"
        return clause


    def isEquivalent(self, otherClause):

        #two equivalent clauses will have the same number of variables
        if len(self.vars) == len(otherClause.vars):
            # if the two clauses are equivalent both clauses must contain the same variables, with the same negations
            # but it does not matter if they are in the same order
            for var in self.vars:
                if otherClause.isInClause(var) == False:
                    return False
            return True
        else:
            return False

    def isInClause(self, otherVar):

        isDefined = False
        for var in self.vars:
            if var.name == otherVar.name and var.neg == otherVar.neg:
                isDefined = True
        return isDefined
