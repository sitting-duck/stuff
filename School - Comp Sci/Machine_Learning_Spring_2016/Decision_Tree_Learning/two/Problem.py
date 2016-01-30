
from __future__ import division
import math
from Training_Data import Training_Data
from Decision_Tree import Decision_Tree

class Problem:

    # all the training examples and functions for accessing them are contained in this object
    training_set = Training_Data()

    # the decision tree and all the functions for manipulating it are contained in this object
    decision_tree = Decision_Tree()

    def __init__(self):
        pass

    def create_decision_tree(self):

        if(self.decision_tree.get_num_nodes() == 0):
            # create the root node
            pass
        # todo: finish this

    def calculate_entropy_for_category(self, category, training_set):
        # wrong
        class_type_frequency = self.get_class_type_frequency_dictionary(training_set)
        # todo: finish calc entropy for variable and test it

    def calculate_entropy_for_training_set(self, training_set):
        class_type_frequency = self.get_class_type_frequency_dictionary(training_set)
        num_values = self.training_set.get_number_training_examples(training_set)

        sum = 0.0
        Pi = 0.0
        Hi = 0.0
        ratio = 0.0

        for key, value in class_type_frequency.iteritems():

            Pi = float(value)/float(num_values)

            # for the edge case of log(0) (convenient loophole for computing entropy)
            if Pi == 0.0:
                sum += 0.0
            else:
                sum += float(-1.0)*float(Pi)*(float(round(math.log(Pi, 2), 3)))
            sum = round(sum, 3)

        return round(sum, 3)

    def get_categories(self):
        return self.training_set.get_categories()

    def get_training_set(self):
        return self.training_set.get_training_set()

    def print_training_set(self, training_set):
        for row in training_set:
            print str(row)

    def get_class_type_frequency_dictionary(self, training_set):
        return self.training_set.get_class_type_frequency_dictionary(training_set)

    def get_class_type_frequency_dictionary_for_category(self, category, training_set):
        return self.training_set.get_class_type_frequency_dictionary(category, training_set)