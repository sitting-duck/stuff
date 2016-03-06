from decimal import Decimal

import math

from Debug import Debug
from ParseTools import ParseTools


class InfoMath:
    def __init__(self):
        pass

    @staticmethod
    def calculate_information_gain_for_category_new(parent_entropy, category, training_set):
        pass

    @staticmethod
    def calculate_entropy_for_category_new(category, parent_branch_attr, training_set):
        pass

    # information gain is a metric to measure the amount of information gained if we split the tree at this category
    @staticmethod
    def calculate_information_gain_for_category(category, parent_branch_attr, parent_node, training_set):

        # noinspection PyComparisonWithNone
        if parent_node is None:

            parent_entropy = InfoMath.calculate_entropy_for_training_set(training_set)

        else:

            parent_entropy = InfoMath.calculate_conditional_entropy_for_attribute(parent_node.category,
                                                                                  parent_branch_attr,
                                                                                  parent_node.training_set)

        training_set_for_category_entropy = InfoMath.calculate_conditional_entropy_for_category(category, training_set)

        information_gain = float(parent_entropy) - float(training_set_for_category_entropy)

        information_gain = InfoMath.abs(information_gain)

        if Debug.level >= 1:
            Debug.log('cat:', category, 'ig:', InfoMath.precision(parent_entropy), '-',
                      InfoMath.precision(training_set_for_category_entropy), '=', information_gain)

        assert information_gain >= 0, 'error: got negative info gain: %s for %s' % (str(information_gain), category)

        return float(information_gain)

    @staticmethod
    def within_acceptable_error(expected, actual, error):
        return InfoMath.abs(expected - actual) <= error

    @staticmethod
    def calculate_conditional_entropy_for_current_node(parent_node, category_for_current_node, parent_branch_attr, training_set):
        if parent_node is None:
            return InfoMath.calculate_conditional_entropy_for_attribute(category_for_current_node, parent_branch_attr, training_set)
        else:
            return InfoMath.calculate_conditional_entropy_for_category(category_for_current_node, training_set)

    @staticmethod
    def calculate_conditional_entropy_for_category(category, training_set):

        current_entropy_sum = 0
        attributes = ParseTools.get_unique_attributes_for_category(category, training_set)

        for attribute in attributes:
            num_current_attribute = float(
                ParseTools.get_number_of_training_examples_for_attribute(category, attribute, training_set))
            num_training_examples = float(ParseTools.get_number_training_examples(training_set))

            pi = float(num_current_attribute / num_training_examples)
            hi = InfoMath.calculate_conditional_entropy_for_attribute(category, attribute, training_set)

            if Debug.level == 4:
                Debug.log('(', InfoMath.precision(pi), ')(', InfoMath.precision(hi), ')', '+')

            if Debug.level == 6:
                Debug.log('(', num_current_attribute, '/', num_training_examples, ')', '*')

            current_entropy_sum += float(pi * hi)

        return float(current_entropy_sum)

    @staticmethod
    def calculate_conditional_entropy_for_attribute(category, attribute, training_set):
        term = 0

        reduced_training_set = ParseTools.get_reduced_training_set(category, attribute, training_set)

        class_type_frequency = ParseTools.get_class_type_frequency_dictionary(reduced_training_set, training_set)

        # get all the training examples where this attribute is present for the given category
        for current_type, num_current_type in class_type_frequency.iteritems():

            reduced_training_set = ParseTools.get_reduced_training_set(category, attribute, training_set)

            num_training_examples_for_current_attribute = ParseTools.get_number_training_examples(reduced_training_set)

            if Debug.level >= 6:
                Debug.log('\t\t\t\t\t\t((-', num_current_type, '/', num_training_examples_for_current_attribute,
                          ')log(', num_current_type, '/', num_training_examples_for_current_attribute, ')', '+')

            pi = float(num_current_type) / float(num_training_examples_for_current_attribute)

            # for the edge case of log(0) (convenient loophole for computing entropy)
            if pi == 0.0:
                term -= 0.0
            else:
                term -= float(pi) * float(math.log(pi, 2))

        return term

    @staticmethod
    def calculate_entropy_for_training_set(training_set):

        current_entropy_sum = 0
        num_training_examples = float(ParseTools.get_number_training_examples(training_set))
        class_types = ParseTools.get_set_of_unique_class_types(training_set)
        num_class_types = len(class_types)
        for i in range(0, num_class_types):
            num_current_type = float(
                ParseTools.get_number_of_training_examples_of_class_type(class_types[i], training_set))

            pi = float(num_current_type / num_training_examples)

            current_entropy_sum -= pi * float(math.log(pi, 2))

        return float(current_entropy_sum)

    @staticmethod
    def precision(number, precision=3):

        # round up to zero if below by acceptable error
        if InfoMath.abs(number) < 0.005 and number < 0:
            number = 0

        return round(Decimal(number), precision)

    @staticmethod
    def abs(value):
        if value < 0:
            return -value
        else:
            return value
