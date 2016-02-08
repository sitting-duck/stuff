
from Training_Data import Training_Data

class Print_Tools:

    def __init_(self):
        pass

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

