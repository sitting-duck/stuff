import copy
from ParseTools import ParseTools


class PrintTools:
    print_tree = []

    def __init__(self):
        pass

    @staticmethod
    def print_in_order(decision_tree, training_set, current_node=None, node_depth=0):

        # since this function is recursive, this check for None indicates that we just called this function the first time
        # this makes sense because we always start printing from root
        if current_node is None:
            current_node = decision_tree.root

        children = decision_tree.get_child_nodes_of(current_node)
        children = PrintTools.sort_by_parent_attr_type(children)

        tab_string = PrintTools.get_tab_string(node_depth)

        for child in children:
            if child.is_leaf is True:
                print tab_string + current_node.category + " = " + child.parent_branch_attr + " : " + child.category
            else:
                print tab_string + current_node.category + " = " + child.parent_branch_attr + " :"
                PrintTools.print_in_order(decision_tree, training_set, child, node_depth + 1)

    def get_print_tree(self, decision_tree, training_set, current_node=None, node_depth=0, print_tree_current=None):

        if print_tree_current is None:
            print_tree_current = []

        self.print_tree = copy.deepcopy(print_tree_current)

        if current_node is None:
            current_node = decision_tree.root

        children = decision_tree.get_child_nodes_of(current_node)
        children = PrintTools.sort_by_parent_attr_type(children)

        tab_string = PrintTools.get_tab_string(node_depth)

        for child in children:
            if child.is_leaf is True:
                self.print_tree.append(
                    tab_string + current_node.category + " = " + child.parent_branch_attr + " : " + child.category + '\n')
            else:
                self.print_tree.append(
                    tab_string + current_node.category + " = " + child.parent_branch_attr + " :" + '\n')
                # self.get_print_tree(decision_tree, training_set, child, node_depth + 1, print_tree)
                self.get_print_tree(decision_tree, training_set, child, node_depth + 1, copy.deepcopy(self.print_tree))
        return self.print_tree

    @staticmethod
    def print_level_order_deprecated_2(decision_tree, training_set):

        deepest_level = decision_tree.get_deepest_level()

        for i in range(0, deepest_level + 1):
            current_level = decision_tree.get_nodes_at_level(i)

            for node in current_level:

                # if training_set.has_category(node.category, training_set.training_set):
                if node.is_leaf is False:
                    attributes = training_set.get_unique_attributes_for_category(node.category,
                                                                                 decision_tree.root.training_set)

                    for attr in attributes:
                        tab_string = PrintTools.get_tab_string(decision_tree.get_level_depth_for_node(node))
                        print tab_string + node.category + " = " + attr + " :"

    @staticmethod
    def get_tab_string(level_num):

        tab_string = ""

        for i in range(0, level_num):
            tab_string += '|\t'

        # tab_string += '\b'

        return tab_string

    @staticmethod
    def get_line_length(decision_tree, training_set):

        longest_category_name_length = PrintTools.get_longest_category_name_length(decision_tree)

        longest_attribute_name_length = PrintTools.get_longest_attribute_name_length(training_set)

        highest_num_children = PrintTools.get_highest_num_children(decision_tree)

        if longest_category_name_length > longest_attribute_name_length:
            return (longest_category_name_length * highest_num_children) + highest_num_children + 2
        else:
            return (longest_attribute_name_length * highest_num_children) + highest_num_children + 2

    @staticmethod
    def get_longest_category_name_length(decision_tree):

        current_longest_name_length = 0

        for node in decision_tree.nodes:
            if len(node.category) > current_longest_name_length:
                current_longest_name_length = len(node.category)

        return current_longest_name_length

    @staticmethod
    def get_longest_attribute_name_length(training_set):

        current_longest_name_length = 0

        categories = ParseTools.get_category_names(training_set)

        for category in categories:
            attributes = ParseTools.get_unique_attributes_for_category(category, training_set)

            for attr in attributes:
                if len(attr) > current_longest_name_length:
                    current_longest_name_length = len(attr)

        return current_longest_name_length

    @staticmethod
    def get_highest_num_children(decision_tree):

        current_highest_num_children = 0

        for node in decision_tree.nodes:
            if len(decision_tree.get_child_nodes_of(node)) > current_highest_num_children:
                current_highest_num_children = len(decision_tree.get_child_nodes_of(node))

        return current_highest_num_children

    @staticmethod
    def print_training_set(training_set):
        for row in training_set:
            print str(row)

    @staticmethod
    def sort_by_parent_attr_type(nodes):
        return sorted(nodes, key=lambda node: node.parent_branch_attr, reverse=False)

    @staticmethod
    def is_all_leaf_nodes(nodes):
        if len(nodes) == 0:
            return False

        for node in nodes:
            if node.is_leaf is False:
                return False
        else:
            return True

    @staticmethod
    def sort_if_all_leaf_nodes(nodes):
        if PrintTools.is_all_leaf_nodes(nodes):
            return sorted(nodes)
        else:
            return nodes
