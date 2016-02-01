import copy

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

    def add_node(self, new_node):
        self.nodes.append(copy.deepcopy(new_node))

    def get_num_nodes(self):
        return len(self.nodes)

    def has_category(self, category):
        for node in self.nodes:
            if node.category == category:
                return True
        return False

    def get_node_with_category(self, category):
        for node in self.nodes:
            if node.category == category:
                return node
            else:
                assert 1 != 1, 'error: there is no node with category %s' % category

    def print_me(self):
        for node in self.nodes:
            node.print_me()
        print ''
