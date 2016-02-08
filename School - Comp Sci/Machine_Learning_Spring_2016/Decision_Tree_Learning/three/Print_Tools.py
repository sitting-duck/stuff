
from Training_Data import Training_Data

class Print_Tools:

    def __init_(self):
        pass
    
    @staticmethod
    def print_level_order_deprecated_2(decision_tree, training_set):

        deepest_level = decision_tree.get_deepest_level()

        for i in range(0, deepest_level + 1):
            current_level = decision_tree.get_nodes_at_level(i)

            for node in current_level:

                #if training_set.has_category(node.category, training_set.training_set):
                if node.is_leaf == False:
                    attributes = training_set.get_unique_attributes_for_category(node.category, decision_tree.root.training_set)

                    for attr in attributes:

                        tab_string = Print_Tools.get_tab_string(decision_tree.get_level_depth_for_node(node))
                        print tab_string + node.category + " = " + attr + " :"

    @staticmethod
    def print_in_order(decision_tree, training_set, current_node, node_depth = 0):

        children = decision_tree.get_child_nodes_of(current_node)

        tab_string = Print_Tools.get_tab_string(node_depth)

        for child in children:
            if child.is_leaf == True:
                print tab_string + current_node.category + " = " + child.parent_branch_attr + " : " + child.category
            else:
                print tab_string + current_node.category + " = " + child.parent_branch_attr + " :"

            Print_Tools.print_in_order(decision_tree, training_set, child, node_depth + 1)

    @staticmethod
    def get_tab_string(level_num):

        tab_string = ""

        for i in range(0, level_num):
            tab_string += '\t'

        return tab_string

    @staticmethod
    def get_line_length(decision_tree, training_set):

        longest_category_name_length = Print_Tools.get_longest_category_name_length(decision_tree)

        longest_attribute_name_length = Print_Tools.get_longest_attribute_name_length(training_set)

        highest_num_children = Print_Tools.get_highest_num_children(decision_tree)

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

        categories = Training_Data.get_category_names(training_set)

        for category in categories:
            attributes = Training_Data.get_unique_attributes_for_category(category, training_set)

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
