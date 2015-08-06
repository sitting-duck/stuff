__author__ = 'ashley'

class Node:
    """ This node class is specific to CSPs.  It contains handles to its parent, sibling, and child nodes, and the current state of the CSP.  Each node in the search tree can be considered a
     step in the solutino of the constraint satisfaction problem (CSP).

     It is important to understand that this node represents a CSP state, it does not represent a variable.
     """
    def __init__(self, parentArg = None, rightSiblingArg = None, currentcspArg = None):

	    # the parent node of the current node.  The parent node represents the step previous to the current step.  We go back in time by tracing up the tree.
        self.parent = parentArg

	    # the right sibling of the current node.  Can be useful to have right sibling for printing in level order.
        self.rightSibling = rightSiblingArg

	    # the children of the current node.  The set of children is the set of possible steps/states that can be reached from the current step/state.
        self.children = []

        # the assignment list contains a list of variables and their assignments.  Each variable is assigned a value from its domain in each step of the solution.
        self.assignment = {}

        # contains the current state of the constraint satisfaction problem.
        # In a given state, all variables have a corresponding value. So, a state is like a set of assignments.
        # Each step in solving the CSP is a try at another assignment of the variables, until one that satisfies all the problem constraints is found.
        # consider this state variable to be a snapshot taken at each step in the solution to the problem.
        self.currentcsp = currentcspArg

    def printAssignment(self):
        print str(self.assignment)