
from Node import Node

class Decision_Tree:

    root = None

    nodes = {}

    def __init__(self):
        pass

    def has_root(self):
        return self.root != None

    def get_num_nodes(self):
        return len(self.nodes)