
from Training_Data import Training_Data

class Node:

    name = ''

    parent = ''

    training_set = Training_Data()

    def __init__(self, name, parent, training_set):

        assert name == '', 'error: Node name cannot be an empty string'
        self.name = name

        assert parent == '', 'error: Node parent name cannot be an empty string'
        self.parent = parent

        self.training_set = training_set

    def set_as_root(self):
        assert self.parent == '' or self.parent == 'none', 'error: cannot set node: ' + self.name + 'as root. Node already has a parent. Root cannot have a parent node.'
        parent = 'none'
        return True

    def is_root(self):
        return self.parent == 'none'

