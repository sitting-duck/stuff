__author__ = 'ashley'

class Node:
    """ This node class is specific to CSPs"""
    def __init__(self, parentArg = None, rightSiblingArg = None, currentcspArg = None):
        self.parent = parentArg
        self.rightSibling = rightSiblingArg
        self.children = []
        self.assignment = {}
        self.currentcsp = currentcspArg

    def printAssignment(self):
        #for var in self.assignment:
        #    # print var.name + ": " + str(self.assignment[var])
        #    print var.name + ": " + str(self.assignment[var])
        #print "\n"

        print str(self.assignment)