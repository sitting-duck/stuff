from decimal import Decimal

import math

from Debug import Debug
from Training_Data import Training_Data


class Info_Math:

    def __init__(self):
        pass

# information gain is a metric to measure the amount of information gained if we split the tree at this category
    @staticmethod
    def calculate_information_gain_for_category(category, parent_branch_attr, parent_node, training_set):
        training_set_for_category_entropy = Info_Math.calculate_conditional_entropy_for_category(category, training_set)

        #parent_entropy = Info_Math.calculate_entropy_for_training_set(training_set)

        if parent_node == None:
            #parent_entropy = Info_Math.calculate_entropy_for_training_set(training_set)
            parent_entropy = Info_Math.calculate_conditional_entropy_for_attribute(category, parent_branch_attr, training_set)
        else:
            #parent_entropy = parent_node.conditional_entropy
            parent_entropy = Info_Math.calculate_conditional_entropy_for_attribute(parent_node.category, parent_branch_attr, parent_node.training_set)

        #information_gain = Info_Math.prec(parent_entropy) - Info_Math.prec(training_set_for_category_entropy)
        information_gain = float(parent_entropy) - float(training_set_for_category_entropy)

        if(Debug.level >= 1):
            Debug.log('cat:', category, 'ig:', Info_Math.prec(parent_entropy), '-', Info_Math.prec(training_set_for_category_entropy), '=', information_gain)

        assert information_gain >= 0, 'error: got negative info gain: %s for %s' % (str(information_gain), category)

        return Info_Math.prec(information_gain)

    @staticmethod
    def calculate_conditional_entropy_for_category(category, training_set):

        sum = 0
        attributes = Training_Data.get_unique_attributes_for_category(category, training_set)

        for attribute in attributes:
            num_current_attribute = float(Training_Data.get_number_of_training_examples_for_attribute(category, attribute, training_set))
            num_training_examples = float(Training_Data.get_number_training_examples(training_set))

            if(Debug.level == 4):
                 Debug.log('(', Info_Math.prec(Pi), ')(', Info_Math.prec(Hi), ')', '+')

            if(Debug.level == 6):
                 Debug.log('(', num_current_attribute, '/', num_training_examples, ')', '*')

            Pi = Info_Math.prec(num_current_attribute / num_training_examples)
            Hi = Info_Math.calculate_conditional_entropy_for_attribute(category, attribute, training_set)

            sum += Info_Math.prec( Pi * Hi)
        return Info_Math.prec(Info_Math.abs(sum))

    @staticmethod
    def calculate_conditional_entropy_for_attribute(category, attribute, training_set):
        term = 0

        reduced_training_set = Training_Data.get_reduced_training_set(category, attribute, training_set)

        class_type_frequency = Training_Data.get_class_type_frequency_dictionary(reduced_training_set, training_set)

        # get all the training examples where this attribute is present for the given category
        for current_type, num_current_type in class_type_frequency.iteritems():

            reduced_training_set = Training_Data.get_reduced_training_set(category, attribute, training_set)

            num_training_examples_for_current_attribute = Training_Data.get_number_training_examples(reduced_training_set)

            if(Debug.level >= 6):
                 Debug.log('\t\t\t\t\t\t((-', num_current_type, '/', num_training_examples_for_current_attribute, ')log(', num_current_type, '/', num_training_examples_for_current_attribute, ')', '+')

            Pi = Info_Math.prec(float(num_current_type))/Info_Math.prec(float(num_training_examples_for_current_attribute))

            # for the edge case of log(0) (convenient loophole for computing entropy)
            if Pi == 0.0:
                term -= 0.0
            else:
                term -= Info_Math.prec(Pi) * Info_Math.prec(math.log(Pi, 2))
                term = Info_Math.prec(term, 3)

        return Info_Math.prec(Info_Math.abs(term), 3)

    @staticmethod
    def calculate_entropy_for_training_set(training_set):

        sum = 0
        num_training_examples = float(Training_Data.get_number_training_examples(training_set))
        class_types = Training_Data.get_set_of_unique_class_types(training_set)
        num_class_types = len(class_types)
        for i in range(0, num_class_types):
            num_current_type = float(Training_Data.get_number_of_training_examples_of_class_type(class_types[i], training_set))

            #Pi = Info_Math.prec(num_current_type / num_training_examples)
            Pi = float(num_current_type / num_training_examples)
            #sum -= Info_Math.prec(Pi)*(Info_Math.prec(math.log(Pi, 2)))
            sum -= (Pi)*float(math.log(Pi, 2))
        #return Info_Math.prec(Info_Math.abs(sum), 3)
        return float(Info_Math.abs(sum))

    @staticmethod
    def prec(number, precision = 3):

        #round up to zero if below by acceptable error
        if(Info_Math.abs(number) < 0.005 and number < 0):
            number = 0

        return round(Decimal(number), precision)

    @staticmethod
    def abs(value):
        if value < 0:
            return -value
        else:
            return value