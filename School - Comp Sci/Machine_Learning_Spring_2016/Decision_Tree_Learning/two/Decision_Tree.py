
from Node import Node

class Decision_Tree:

    root = Node()

    nodes = {}

    def __init__(self):
        pass

    def get_num_nodes(self):
        return len(self.nodes)