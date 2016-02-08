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

        queue = []
        queue.append(self.root)

        print self.root.category

        while len(queue) > 0:
            current_node = queue[0]
            del queue[0]

            next_level = self.get_child_nodes_of(current_node)
            queue.append(next_level)
            print "\n"
            self.print_level(next_level)

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


