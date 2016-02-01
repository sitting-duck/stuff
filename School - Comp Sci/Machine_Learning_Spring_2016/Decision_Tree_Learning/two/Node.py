
from Training_Data import Training_Data

class Node:

    category = ''

    parent = None

    training_set = Training_Data()

    is_leaf = False

    #add is leaf default param

    def __init__(self, category, parent, training_set, is_leaf = False):

        assert category != '', 'error: Node category cannot be an empty string'
        self.category = category

        assert parent != '', 'error: Node parent name cannot be an empty string'
        self.parent = parent

        self.training_set = training_set

        self.is_leaf = is_leaf

    def is_root(self):
        return self.parent == None

    def is_leaf(self):
        return self.is_leaf()

    def print_me(self):
        print 'cat: ' + str(self.category) + ' par: ' + self.str(self.parent)

    def str(self, node):
        if node == None:
            return 'none'
        else:
            return node.category