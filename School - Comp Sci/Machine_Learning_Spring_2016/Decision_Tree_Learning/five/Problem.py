
from __future__ import division
from itertools import groupby as groupby_handle

import copy
from decimal import *
import math

from Info_Math import Info_Math
from Print_Tools import Print_Tools
from Tests import Tests
from Training_Data import Training_Data
from Decision_Tree import Decision_Tree
from Node import Node
from Debug import Debug

class Problem:

    # all the training examples and functions for accessing them are contained in this object
    training_set = Training_Data()

    # the decision tree and all the functions for manipulating it are contained in this object
    decision_tree = Decision_Tree()

    print_tools = Print_Tools()

    def __init__(self):

        self.tests = Tests()
        self.tests.get_test_data_from_file(self)

    def create_decision_tree(self, training_set, parent_branch_attr = None, parent_node = None):

        print "\n\n"

        if len(training_set) == 0:
            return self.decision_tree

        # if we have reached a leaf node, exit this recursive thread
        if(self.append_leaf_node_to_tree_and_exit_if_single_category(parent_node, training_set, parent_branch_attr)):
            return self.decision_tree

        if len(Training_Data.get_category_names(training_set)) == 0:
            return self.decision_tree

        category_for_current_node = self.get_best_category_for_node(training_set, parent_branch_attr, parent_node)
        #conditional_entropy_for_current_node = Info_Math.calculate_conditional_entropy_for_category(category_for_current_node, training_set)
        conditional_entropy_for_current_node = Info_Math.calculate_conditional_entropy_for_attribute(category_for_current_node, parent_branch_attr, training_set)

        if(Debug.level >= 1):
            Debug.log('selected', category_for_current_node, 'for current node.', "it's parent:", Decision_Tree.get_node_string(parent_node))

        if category_for_current_node == None:
            return self.decision_tree

        # the current category column will be removed
        partitions = self.get_training_set_partitions_by_attribute(category_for_current_node, training_set)

        # these are sorted by alpha
        attributes = sorted(self.training_set.get_unique_attributes_for_category(category_for_current_node, training_set))

        current_node = self.add_node_to_tree(category_for_current_node, conditional_entropy_for_current_node, parent_node, training_set, False, parent_branch_attr)

        for attribute in attributes:
            self.create_decision_tree(partitions[attribute], attribute, current_node)

        return self.decision_tree

    #returns true if we've reached a leaf node and it's time to bail out of this recursive thread
    def append_leaf_node_to_tree_and_exit_if_single_category(self, parent_node, training_set, parent_branch_attr):
        was_homogenous = self.training_set.is_homogeneous(training_set)

        categories = Training_Data.get_category_names(training_set)
        num_categories = len(categories)

        #if num_categories == 1:
        #if parent_node != None:
        #    num_attributes = len(Training_Data.get_unique_attributes_for_category(parent_node.category, training_set))
        #else:
        #    num_attributes = 999

        if(Debug.level == 5):
            Debug.log('was_homogenous?', was_homogenous)
            Print_Tools.print_training_set(training_set)

        #if was_homogenous and (num_categories == 1) and num_attributes == 1:
        #if was_homogenous and (num_categories == 1):
        if num_categories == 0 or was_homogenous:
        #if num_categories == 1 and num_attributes == 1:
        #if num_attributes == 1:
        #if was_homogenous == True:
            self.add_leaf_to_tree(parent_node, training_set, parent_branch_attr)
            return True
        else:
            return False

    def add_leaf_to_tree(self, parent_node, training_set, parent_branch_attr):

        type = self.get_most_common_class_type(training_set)

        parent_conditional_entropy = Problem.get_parent_conditional_entropy(parent_node)

        # add the parent
        self.add_node_to_tree(str(type), parent_conditional_entropy, parent_node, training_set, True, parent_branch_attr)

    @staticmethod
    def get_parent_conditional_entropy(parent_node):
        if parent_node == None:
            return None
        else:
            return parent_node.conditional_entropy

    @staticmethod
    def get_most_common_class_type(training_set):
        #if len(training_set[0]) > 1:
        #    type_dic = Training_Data.get_class_type_frequency_dictionary(training_set)

        #    most_common_types = max(len(type_instances) for type_instances in type_dic.itervalues())

        #    alpha_ordered_most_common_types = sorted(most_common_types)

        #    return alpha_ordered_most_common_types[0]

        #for line in training_set:
        #    del line[0]

        # get rid of the class category tag
        #temp = copy.deepcopy(training_set)
        #del temp[0]

        #else:
        #most_common = (max(groupby_handle(training_set), key=lambda (x, items_of_current_class_type):(len(list(items_of_current_class_type)), -training_set.index(x)))[0])[0]
        #return most_common

        #type_dic = Training_Data.get_class_type_frequency_dictionary(training_set)

        type_dic = {}
        class_types = Training_Data.get_set_of_unique_class_types(training_set)
        for type in class_types:
            num_of_type = Training_Data.get_number_of_training_examples_of_class_type(type, training_set)
            type_dic[type] = num_of_type

        for key, value in type_dic.iteritems():
            print "key: " + key + " value: " + str(value)

        greatest_current_key = ''
        greatest_num_items = 0

        #determine what the greatest number of items is
        for key, value in type_dic.iteritems():
            if value > greatest_num_items:
                greatest_num_items = value

        #find all keys with that many items
        # in the case of a tie we will take the lowest alpha key
        keys = []
        for key, value in type_dic.iteritems():
            if value == greatest_num_items:
                keys.append(key)

        most_common = sorted(keys)[0]

        return most_common

    def get_training_set_partitions_by_attribute(self, category, training_set):

        if category == None:
            return

        attributes = self.training_set.get_unique_attributes_for_category(category, training_set)
        partitions = {}

        for attribute in attributes:
            temp_partition = self.training_set.get_training_set_for_single_attribute(category, attribute, training_set)

            #partitions[attribute] = temp_partition
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

    def get_best_category_for_node(self, training_set, parent_branch_attr, parent_node = None):
        current_best_information_gain = 0
        current_best_category  = None

        categories = self.training_set.get_category_names(training_set)

        for category in categories:

            current_information_gain = Info_Math.calculate_information_gain_for_category(category, parent_branch_attr, parent_node, training_set)

            #if they have the same information gain, take the one that is alphabetically lower
            if current_information_gain == current_best_information_gain:
                current_best_category = Training_Data.get_lowest_alpha_category((category, current_best_category))

            #if current is better then take current
            if current_information_gain > current_best_information_gain:
                current_best_information_gain = current_information_gain
                current_best_category = category

        #eg.  if all categories had entropy of zero
        #and we have not exhasusted all categories yet
        if current_best_category == None and len(categories) > 0:
            current_best_category = Training_Data.get_lowest_alpha_category(categories)

        return current_best_category

    def get_training_set(self):
        return self.training_set.get_training_set()

    def add_node_to_tree(self, category, conditional_entropy, parent_node, training_set, is_leaf, parent_branch_attr):
        current_node = Node(category, conditional_entropy, parent_node, training_set, is_leaf, parent_branch_attr)
        self.decision_tree.add_node(current_node)

        if Debug.level >= 3:
            Print_Tools.print_in_order(self.decision_tree, self.training_set)

        #Print_Tools.check_in_order(self.decision_tree, self.training_set)

        print_tree = self.print_tools.get_print_tree(self.decision_tree, self.training_set)
        #print "curr: " + str(print_tree)
        self.tests.test_tree_for_equality(print_tree)

        return current_node