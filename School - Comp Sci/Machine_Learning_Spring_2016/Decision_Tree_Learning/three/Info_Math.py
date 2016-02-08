from decimal import Decimal

import math

from Debug import Debug
from Training_Data import Training_Data


class Info_Math:

    def __init__(self):
        pass

# information gain is a metric to measure the amount of information gained if we split the tree at this category
    @staticmethod
    def calculate_information_gain_for_category_for_undefined_root(category, training_set):
        training_set_entropy = Info_Math.calculate_entropy_for_training_set(training_set)
        information_gain = Info_Math.calculate_information_gain_for_category(category, training_set_entropy, training_set)

        return Info_Math.prec(Info_Math.abs(information_gain))

    @staticmethod
    def calculate_entropy_for_category(category, training_set):

        sum = 0
        attributes = Training_Data.get_unique_attributes_for_category(category, training_set)

        for attribute in attributes:
            num_current_attribute = Training_Data.get_number_of_training_examples_for_attribute(category, attribute, training_set)
            num_training_examples = Training_Data.get_number_training_examples(training_set)

            Pi = Info_Math.prec(num_current_attribute / num_training_examples)
            Hi = Info_Math.calculate_entropy_for_attribute(category, attribute, training_set)

            if(Debug.level >= 4):
                 Debug.log('(', Info_Math.prec(Pi), ')(', Info_Math.prec(Hi), ')', '+')

            sum += Info_Math.prec( Pi * Hi)
        return Info_Math.prec(Info_Math.abs(sum))

    @staticmethod
    def calculate_entropy_for_attribute(category, attribute, training_set):
        sum = 0

        # get all the training examples where this attribute is present for the given category
        reduced_training_set = Training_Data.get_training_set_for_single_attribute(category, attribute, training_set)
        class_type_frequency = Training_Data.get_class_type_frequency_dictionary(reduced_training_set)
        num_training_examples_for_current_attribute = Training_Data.get_number_training_examples(reduced_training_set)
        for current_type, num_current_type in class_type_frequency.iteritems():

            Pi = Info_Math.prec(num_current_type)/Info_Math.prec(num_training_examples_for_current_attribute)

            # for the edge case of log(0) (convenient loophole for computing entropy)
            if Pi == 0.0:
                sum = 0.0
            else:
                sum -= Info_Math.prec(Pi) * Info_Math.prec(math.log(Pi, 2))
            sum = Info_Math.prec(sum, 3)

        if sum < 0:
            return 0
        return Info_Math.prec(Info_Math.abs(sum), 3)

    @staticmethod
    def calculate_entropy_for_training_set(training_set):

        sum = 0
        num_training_examples = Training_Data.get_number_training_examples(training_set)
        class_types = Training_Data.get_set_of_unique_class_types(training_set)
        num_class_types = len(class_types)
        for i in range(0, num_class_types):
            num_current_type = Training_Data.get_number_of_training_examples_of_class_type(class_types[i], training_set)
            Pi = Info_Math.prec(num_current_type / num_training_examples)
            sum -= Info_Math.prec(Pi)*(Info_Math.prec(math.log(Pi, 2)))
        return Info_Math.prec(Info_Math.abs(sum), 3)

    @staticmethod
    def prec(number, precision = 3):
        return round(Decimal(number), precision)

    @staticmethod
    def abs(value):
        if value < 0:
            return -value
        else:
            return value