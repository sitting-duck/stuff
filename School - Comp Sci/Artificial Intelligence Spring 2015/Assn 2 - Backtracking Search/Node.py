__author__ = 'ashley'

class Node:
    """ This node class is specific to CSPs.  It contains handles to its parent, sibling, and child nodes, and the current state of the CSP.  Each node in the search tree can be considered a
     step in the solutino of the constraint satisfaction problem (CSP)."""
    def __init__(self, parentArg = None, rightSiblingArg = None, currentcspArg = None):
        self.parent = parentArg
        self.rightSibling = rightSiblingArg
        self.children = []

        # the assignment list contains a list of variables and their assignments.  Each variable is assigned a value from its domain in each step of the solution.
        self.assignment = {}

        # contains the current state of the constraint satisfaction problem.
        # In a given state, all variables have a corresponding value. So, a state is like a set of assignments.
        # Each step in solving the CSP is a try at another assignment of the variables, until one that satisfies all the problem constraints is found.
        # consider this state variable to be a snapshot taken at each step in the solution to the problem.
        self.currentcsp = currentcspArg

    def printAssignment(self):
        for var in self.assignment:
            print var.name + ": " + str(self.assignment[var])
        print "\n"

        print str(self.assignment)