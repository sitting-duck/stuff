
from __future__ import division
import math
from Training_Data import Training_Data
from Decision_Tree import Decision_Tree

class Problem:

    # all the training examples and functions for accessing them are contained in this object
    training_data = Training_Data()

    # the decision tree and all the functions for manipulating it are contained in this object
    decision_tree = Decision_Tree()

    def __init__(self):
        pass

    def create_decision_tree(self):

        if(self.decision_tree.get_num_nodes() == 0):
            # create the root node
            pass

    def calculate_entropy_for_variable(self, variable):
        proportion_to_class_type_for_training_set = self.get_proportion_to_class_type_for_training_set_dictionary()
        # todo: finish calc entropy for variable and test it

    def calculate_entropy_for_training_set(self):
        proportion_to_class_type_for_training_set = self.get_proportion_to_class_type_for_training_set_dictionary()
        num_values = self.training_data.get_number_training_examples()

        sum = 0.0
        Pi = 0.0
        Hi = 0.0
        ratio = 0.0

        for key, value in proportion_to_class_type_for_training_set.iteritems():

            Pi = float(value)/float(num_values)

            # for the edge case of log(0) (convenient loophole for computing entropy)
            if Pi == 0.0:
                sum += 0.0
            else:
                sum += float(-1.0)*float(Pi)*(float(round(math.log(Pi, 2), 3)))
            sum = round(sum, 3)

        return round(sum, 3)

    def get_categories(self):
        return self.training_data.get_categories()

    def get_tokenized_data(self):
        return self.training_data.get_tokenized_data()

    def get_proportion_to_class_type_for_training_set_dictionary(self):
        return self.training_data.get_proportion_to_class_type_for_training_set_dictionary()

