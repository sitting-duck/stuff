from __future__ import division
from utils.InfoMath import InfoMath
from utils.PrintTools import PrintTools
from testing.unit_testing.UnitTests import UnitTests
from utils.ParseTools import ParseTools
from tree.DecisionTree import DecisionTree
from tree.Node import Node
from utils.Debug import Debug


class Training:
    """
        This class will train and build the decision tree with a set of training examples
    """
    # all the training examples and functions for accessing them are contained in this object
    training_data = ParseTools()

    # the decision tree and all the functions for manipulating it are contained in this object
    decision_tree = DecisionTree()

    print_tools = PrintTools()

    def __init__(self):

        self.tests = UnitTests()

        self.training_set = ParseTools.get_training_set()

        self.tests.run_tests(self)

    def create_decision_tree(self, training_set, parent_branch_attr=None, parent_node=None):

        # if we have reached a leaf node, exit this recursive thread
        if self.append_leaf_node_to_tree_and_exit_if_single_category(parent_node, training_set, parent_branch_attr):
            return self.decision_tree

        category_for_current_node = self.get_best_category_for_node(training_set, parent_branch_attr, parent_node)

        conditional_entropy_for_current_node = InfoMath.calculate_conditional_entropy_for_current_node(parent_node, category_for_current_node, parent_branch_attr, training_set)

        if Debug.level >= 1:
            Debug.log('selected', category_for_current_node, 'for current node.', "it's parent:",
                      DecisionTree.get_node_string(parent_node))

        # the current category column will be removed in the training sets passed down to the child nodes
        partitions = ParseTools.get_training_set_partitions_by_attribute(category_for_current_node, training_set)

        attributes = ParseTools.get_unique_attributes_for_category(category_for_current_node, training_set)

        current_node = self.add_node_to_tree_and_test_current_tree(category_for_current_node, conditional_entropy_for_current_node,
                                                                   parent_node, training_set, False, parent_branch_attr)

        for attribute in attributes:
            self.create_decision_tree(partitions[attribute], attribute, current_node)

        return self.decision_tree

        # returns true if we've reached a leaf node and it's time to exit out of this recursive thread

    def append_leaf_node_to_tree_and_exit_if_single_category(self, parent_node, training_set, parent_branch_attr):

        if ParseTools.is_leaf(training_set):

            self.add_leaf_to_tree(parent_node, training_set, parent_branch_attr)
            return True
        else:
            return False

    def add_leaf_to_tree(self, parent_node, training_set, parent_branch_attr):

        current_leaf_type = self.get_type_for_leaf(training_set)

        parent_conditional_entropy = Node.get_parent_conditional_entropy(parent_node)

        # add the parent
        self.add_node_to_tree_and_test_current_tree(str(current_leaf_type), parent_conditional_entropy, parent_node, training_set, True,
                                                    parent_branch_attr)

    def get_type_for_leaf(self, training_set):

        # select the most common type in the global training set
        # when the training set has zero training examples
        if ParseTools.get_number_training_examples(training_set) == 0:
            return ParseTools.get_most_common_class_type(self.training_set)

        else:

            # select the most common type in the local training set
            # when  the training set is not pure but there are no categories left and there is more than zero examples
            if ParseTools.is_pure(training_set) == False and ParseTools.get_num_categories(training_set) == 0:
                return ParseTools.get_most_common_class_type(training_set)

            else:
                return ParseTools.get_most_common_class_type(training_set)

    # partition the training examples by class type
    def get_training_set_partitions_by_class_type(self, training_set):

        training_set_partitions = {}
        current_training_subset = []

        for unique_class_type in self.training_data.get_set_of_unique_class_types(training_set):
            for example in training_set:
                if example[-1] == unique_class_type:
                    current_training_subset.append(example)
            training_set_partitions[unique_class_type] = current_training_subset
        return training_set_partitions

    def get_best_category_for_node(self, training_set, parent_branch_attr, parent_node=None):
        current_best_information_gain = 0
        current_best_category = None

        categories = self.training_data.get_category_names(training_set)

        for category in categories:

            current_information_gain = InfoMath.calculate_information_gain_for_category(category, parent_branch_attr,
                                                                                        parent_node, training_set)

            # if current is better then take current
            if current_information_gain > current_best_information_gain:
                current_best_information_gain = current_information_gain
                current_best_category = category

        # eg.  if all categories had entropy of zero
        # and we have not exhausted all categories yet
        if current_best_category is None and len(categories) > 0:
            current_best_category = ParseTools.get_lowest_alpha_category(categories)

        return current_best_category

    def add_node_to_tree_and_test_current_tree(self, category, conditional_entropy, parent_node, training_set, is_leaf, parent_branch_attr):
        current_node = Node(category, conditional_entropy, parent_node, training_set, is_leaf, parent_branch_attr)

        self.decision_tree.add_node(current_node)

        if Debug.level >= 3:
            PrintTools.print_in_order(self.decision_tree, self.training_data)

        print_tree = self.print_tools.get_print_tree(self.decision_tree, self.training_data)
        self.tests.test_tree_for_equality(print_tree)

        return current_node
