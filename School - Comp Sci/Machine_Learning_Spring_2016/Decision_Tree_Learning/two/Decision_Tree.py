
from Node import Node

class Decision_Tree:

    root = None

    nodes = []

    def __init__(self):
        pass

    def has_root(self):
        return self.root != None

    def set_root(self, node):
        self.root = node
        self.nodes.append(self.root)

    def get_num_nodes(self):
        return len(self.nodes)

    def print_me(self):
        for node in self.nodes:
            node.print_me()
