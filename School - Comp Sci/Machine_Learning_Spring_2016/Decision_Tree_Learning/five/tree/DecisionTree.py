
class DecisionTree:

    def __init__(self):
        self.root = None
        self.nodes = []

    def has_root(self):
        return self.root is not None

    def set_root(self, node):
        self.root = node

    def add_node(self, new_node):
        if len(self.nodes) == 0:
            self.set_root(new_node)
        self.nodes.append(new_node)

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

    def get_node_with(self, parent_node, parent_branch_attr):

        for node in self.nodes:
            if node.parent is parent_node and parent_branch_attr == node.parent_branch_attr:
                return node

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

            if self.nodes[i].parent is None:
                continue

            if self.nodes[i].parent is current_node:
                child_nodes.append(self.nodes[i])

        return child_nodes

    @staticmethod
    def get_level_depth_for_node(current_node):

        level_depth = 0

        while current_node.parent is not None:
            current_node = current_node.parent
            level_depth += 1

        return level_depth

    @staticmethod
    def print_level(level):
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

    @staticmethod
    def get_node_string(node):
        if node is None:
            return 'none'
        else:
            return node.category
