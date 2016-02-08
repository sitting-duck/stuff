
from __future__ import division

import copy
from decimal import *
import math

from Info_Math import Info_Math
from Print_Tools import Print_Tools
from Training_Data import Training_Data
from Decision_Tree import Decision_Tree
from Node import Node
from Debug import Debug

class Problem:

    # all the training examples and functions for accessing them are contained in this object
    training_set = Training_Data()

    # the decision tree and all the functions for manipulating it are contained in this object
    decision_tree = Decision_Tree()

    def __init__(self):
        pass

    def create_decision_tree(self, training_set, parent_branch_attr = None, parent_node = None):

        print "\n\n"

        if len(training_set) == 0:
            return self.decision_tree

        # if we have reached a leaf node, exit this recursive thread
        if( self.append_leaf_node_to_tree_and_exit_if_homogenous(parent_node, training_set, parent_branch_attr) ):
            return

        category_for_current_node = self.get_best_category_for_node(training_set, parent_node)
        conditional_entropy_for_current_node = Info_Math.calculate_entropy_for_category(category_for_current_node, training_set)

        if(Debug.level >= 1):
            Debug.log('selected', category_for_current_node, 'for current node.', "it's parent:", Decision_Tree.get_node_string(parent_node))

        assert category_for_current_node != None, 'the fuck dude? None is not a category!'

        if Debug.level >= 3:
            Debug.log('das tree:')
            self.decision_tree.print_me()

        if Debug.level == 0:
            Print_Tools.print_in_order(self.decision_tree, self.training_set, self.decision_tree.root)

        partitions = self.get_training_set_partitions_by_attribute(category_for_current_node, training_set)
        attributes = self.training_set.get_unique_attributes_for_category(category_for_current_node, training_set)

        current_node = Node(category_for_current_node, conditional_entropy_for_current_node, parent_node, training_set, False, parent_branch_attr)
        self.decision_tree.add_node(current_node)

        for attribute in attributes:
            self.create_decision_tree(partitions[attribute], attribute, current_node)

        return copy.deepcopy(self.decision_tree)

    #returns true if we've reached a leaf node and it's time to bail out of this recursive thread
    def append_leaf_node_to_tree_and_exit_if_homogenous(self, parent_node, training_set, parent_branch_attr):
        was_homogenous = self.training_set.is_homogeneous(training_set)

        if(Debug.level == 5):
            Debug.log('homo?', was_homogenous)
            Print_Tools.print_training_set(training_set)

        if was_homogenous:
            type = self.training_set.get_set_of_unique_class_types(training_set)
            if parent_node == None:
                new_node = Node(str(type[0]), None, parent_node, training_set, True, parent_branch_attr)
            else:
                new_node = Node(str(type[0]), parent_node.conditional_entropy, parent_node, training_set, True, parent_branch_attr)
            self.decision_tree.add_node(new_node)
            return True
        else:
            return False

    def get_training_set_partitions_by_attribute(self, category, training_set):

        if category == None:
            return

        attributes = self.training_set.get_unique_attributes_for_category(category, training_set)
        partitions = {}

        temp_training_set = copy.deepcopy(training_set)
        for example in training_set:
            for attribute in attributes:
                temp_partition = self.training_set.get_training_set_for_single_attribute(category, attribute, training_set)

                partitions[attribute] = self.training_set.get_training_set_with_category_removed(category, temp_partition)


        return partitions

    # possibly useless
    def get_training_set_partitions_by_class_type(self, training_set):
        #partition the training examples by class type
        training_set_partitions = {}
        current_training_subset = []
        child_nodes = []
        for type in self.training_set.get_set_of_unique_class_types():
            for example in training_set:
                if example[-1] == type:
                    current_training_subset.append(example)
            training_set_partitions[type] = current_training_subset
        return training_set_partitions

    #calculate the information gain for all the categories and store which one
    #has the highest information gain
    #def get_best_category_for_root(self, training_set):
    #    current_best_information_gain = 0
    #    current_best_category  = None
    #    categories = Training_Data.get_category_names(training_set)

    #    for category in categories:
    #        current_information_gain = Info_Math.calculate_information_gain_for_category_for_undefined_root(category, self.get_training_set())
    #        if current_information_gain > current_best_information_gain:
    #            current_best_information_gain = current_information_gain
    #            current_best_category = category

    #    return current_best_category

    def get_best_category_for_node(self, training_set, parent_node = None):
        current_best_information_gain = 0
        current_best_category  = None

        categories = self.training_set.get_category_names(training_set)

        for category in categories:

            current_information_gain = Info_Math.calculate_information_gain_for_category(category, parent_node, training_set)
            if current_information_gain > current_best_information_gain:
                current_best_information_gain = current_information_gain
                current_best_category = category

        return current_best_category

    def get_training_set(self):
        return self.training_set.get_training_set()
