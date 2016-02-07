import copy

from Node import Node

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
            self.set_root(new_node)
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

    def print_level_order(self):

        current_level = []
        current_level.append(self.root)

        print self.root.category

        while len(current_level) > 0:
            current_node = current_level[0]
            del current_level[0]

            # for every node in this tree
            for i in range(0, len(self.nodes)):
                #if it's parent is the current node add it to the current level
                if self.nodes[i].parent == None:
                    continue
                if self.nodes[i].parent.category == current_node.category:
                    current_level.append(self.nodes[i])

            # now that we've got the level, print the level
            for item in current_level:
                print " " + item.category + " ",
            print ""

    def get_child_nodes_of(self, current_node):
        child_nodes = []

        for i in range(0, len(self.nodes)):

            if self.nodes[i].parent == None:
                continue

            if self.nodes[i].parent.category == current_node.category:
                child_nodes.append(self.nodes[i])

        return child_nodes

