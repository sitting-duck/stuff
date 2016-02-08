import copy

from Node import Node
from Training_Data import Training_Data

class Decision_Tree:

    def __init__(self):
         self.root = None
         self.nodes = []

    def has_root(self):
        return self.root != None

    def set_root(self, node):
        self.root = node

    def add_node(self, new_node):
        if len(self.nodes) == 0:
            self.set_root(copy.deepcopy(new_node))
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

    def print_level_order_deprecated(self):

        deepest_level = self.get_deepest_level()

        for i in range(0, deepest_level + 1):
            current_level = self.get_nodes_at_level(i)
            self.print_level(current_level)

    def get_next_level(self, current_node):
        pass

    def get_child_nodes_of(self, current_node):
        child_nodes = []

        for i in range(0, len(self.nodes)):

            if self.nodes[i].parent == None:
                continue

            if self.nodes[i].parent.category == current_node.category:
                child_nodes.append(self.nodes[i])

        return child_nodes

    def get_level_depth_for_node(self, current_node):

        level_depth = 0

        while current_node.parent != None:
            current_node = current_node.parent
            level_depth += 1

        return level_depth

    def print_level(self, level):
        for node in level:
            print node.category + " ",
        print ""

    def get_nodes_at_level(self, level_number):
        level_nodes = []

        for node in self.nodes:
            if self.get_level_depth_for_node(node) == level_number:
                level_nodes.append(node)

        return level_nodes

    def get_deepest_level(self):

        current_deepest_level = 0
        for node in self.nodes:
            current_node_level_depth = self.get_level_depth_for_node(node)
            if current_node_level_depth > current_deepest_level:
                current_deepest_level = current_node_level_depth

        return current_deepest_level
