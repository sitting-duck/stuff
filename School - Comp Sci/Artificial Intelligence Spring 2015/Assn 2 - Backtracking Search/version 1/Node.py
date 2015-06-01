__author__ = 'ashley'


class Node:
        """ This node class is specific to CSPs"""

        def __init__(self, parentArg = None):
            self.parent = parentArg
            self.assignment = {}