
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

    def calculate_information_gain_for_category(self, category, training_set):

        parent_entropy = self.calculate_entropy_for_training_set(training_set)



    def fail_calculate_entropy_for_category(self, category, training_set):

        #category_frequency_dictionary = self.get_class_type_frequency_dictionary_for_category(category, training_set)

        sum = 0
        Hi = 0
        Pi = 0

        # for each attribute
        for attribute in self.training_set.get_unique_attributes_for_category(category, training_set):
            reduced_training_set = self.training_set.get_training_set_for_single_attribute(category, attribute, training_set)
            num_current_attr = len(reduced_training_set)
            num_training_examples = len(training_set)
            attr_proportion = float(num_current_attr / num_training_examples)

            # for each class type
            for type in self.training_set.get_set_of_unique_class_types(self.get_training_set()):
                num_of_type = self.training_set.get_number_of_training_examples_of_class_type(type, reduced_training_set)
                Pi = float(float(num_of_type) / float(num_current_attr))
                print "Pi: " + str(Pi)
                if Pi == 0:
                    term = 0
                else:
                    term = Pi * math.log(Pi, 2)
                Hi -= term

            sum += float(attr_proportion * Hi)
        return round(sum, 3)

    def calculate_entropy_for_category(self, category, training_set):

        category_frequency_dictionary = self.get_class_type_frequency_dictionary_for_category(category, training_set)

        num_training_examples = self.training_set.get_number_training_examples(training_set)

        sum = 0
        for attribute in category_frequency_dictionary.keys():

            num_attribute_instances = len(self.training_set.get_training_set_for_single_attribute(category, attribute, training_set)) - 1

            attribute_proportion = round(float(     round(float(num_attribute_instances), 3) / round(float(num_training_examples), 3)), 3)

            HiPi = 0
            for type in category_frequency_dictionary[attribute].keys():
                current_type = category_frequency_dictionary[attribute]
                num_of_current_type = category_frequency_dictionary[attribute][current_type.keys()[0]]
                Pi = round( float(   round(float(num_of_current_type), 3) / round(float(num_attribute_instances), 3)     ), 3)
                HiPi -= round( float( Pi * round(float(math.log(Pi, 2)), 3) ), 3)

            sum += round( float( attribute_proportion * HiPi ), 3)
        return sum
    #todo: test

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
        return self.training_set.get_class_type_frequency_dictionary_for_category(category, training_set)