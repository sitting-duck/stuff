class Node:

    def __init__(self, category, conditional_entropy, parent, training_set, is_leaf, parent_branch_attr):

        assert category != '', 'error: Node category cannot be an empty string'
        self.category = category

        self.conditional_entropy = conditional_entropy

        assert parent != '', 'error: Node parent name cannot be an empty string'
        self.parent = parent

        self.training_set = training_set

        self.is_leaf = is_leaf

        self.parent_branch_attr = parent_branch_attr

    def is_root(self):
        return self.parent is None

    def is_leaf(self):
        return self.is_leaf()

    def print_me(self):
        print 'cat: ' + str(self.category) + ' par: ' + self.str(self.parent)

    @staticmethod
    def str(node):
        if node is None:
            return 'none'
        else:
            return node.category

    @staticmethod
    def get_parent_conditional_entropy(parent_node):
        if parent_node is None:
            return None
        else:
            return parent_node.conditional_entropy
