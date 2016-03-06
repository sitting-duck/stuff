import copy
from tree.Node import Node
from tree.DecisionTree import DecisionTree


class UnitTestsPlayTennis:
    def __init__(self):
        pass

    @staticmethod
    def run_tests(problem):
        UnitTestsPlayTennis.run_training_set_tests(problem)
        UnitTestsPlayTennis.run_problem_tests(problem)
        UnitTestsPlayTennis.run_decision_tree_tests(problem)
        UnitTestsPlayTennis.run_curiosity_tests()

    @staticmethod
    def run_problem_tests(problem):
        UnitTestsPlayTennis.test_calculate_information_gain_for_category(problem)
        UnitTestsPlayTennis.test_calculate_information_gain_for_category_for_undefined_root(problem)
        UnitTestsPlayTennis.test_calculate_entropy_for_training_set(problem)
        UnitTestsPlayTennis.test_calculate_entropy_for_attribute(problem)
        UnitTestsPlayTennis.test_calculate_entropy_for_category(problem)
        UnitTestsPlayTennis.test_precision(problem)
        UnitTestsPlayTennis.test_create_decision_tree(problem)
        UnitTestsPlayTennis.test_get_node_string(problem)

    @staticmethod
    def run_decision_tree_tests(problem):
        UnitTestsPlayTennis.test_get_child_nodes_of()
        UnitTestsPlayTennis.test_get_level_depth_for_node()
        UnitTestsPlayTennis.test_get_deepest_level()
        UnitTestsPlayTennis.test_got_correct_decision_tree(problem)

    @staticmethod
    def run_training_set_tests(problem):

        # takes the text data from the input file and returns a 2D list of the training data
        UnitTestsPlayTennis.test_get_tokenized_data(problem)

        # returns the row including the training data id and class of the training set
        UnitTestsPlayTennis.test_get_row(problem)

        # returns the column including the category name of the training set
        UnitTestsPlayTennis.test_get_column(problem)

        # returns a list of the category names in the order they are listed in the training set
        UnitTestsPlayTennis.test_get_category_names(problem)

        # returns the set of attribute types for a category
        UnitTestsPlayTennis.test_get_unique_attributes_for_category(problem)

        # returns the set of attribute types from category column in the training data
        UnitTestsPlayTennis.test_get_unique_attribute_names_from_column(problem)

        # returns the index of the last column of the training set
        UnitTestsPlayTennis.test_get_index_of_class_column(problem)

        # returns the set of class types for a category
        UnitTestsPlayTennis.test_get_set_of_unique_class_types(problem)

        # takes an index and returns the category name for that column
        UnitTestsPlayTennis.test_get_category_name_from_column(problem)

        # takes an index and returns a dictionary with the count for all the attributes for a category set to zero
        UnitTestsPlayTennis.test_create_attribute_dictionary_from_column(problem)

        # takes an index and returns a tuple with the name of the category and a dictionary of all its attributes with
        # their counts set to zero
        UnitTestsPlayTennis.test_create_category_tuple_from_column(problem)

        # returns a dictionary of all the categories with attribute counts all set to zero#
        UnitTestsPlayTennis.test_create_categories_from_training_set(problem)

        # return the set of class types for the training set
        UnitTestsPlayTennis.test_get_class_values_for_training_set(problem)

        # returns the number of training examples that have been classified a certain way
        # useful for calculating entropy
        UnitTestsPlayTennis.test_get_number_of_training_examples_of_class_type(problem)

        # returns a dictionary with the counts for each class type
        UnitTestsPlayTennis.test_get_class_type_frequency_dictionary(problem)

        # returns the number of training examples in the given training set
        UnitTestsPlayTennis.test_get_number_training_examples(problem)

        # returns a bool indicating whether a training set has some category
        # useful for input validation
        UnitTestsPlayTennis.test_has_category(problem)

        # returns the index of the column for given category in the training set
        UnitTestsPlayTennis.test_get_index_of_column_for_category(problem)

        # returns the actual column in the training set for given category
        UnitTestsPlayTennis.test_get_column_for_category(problem)

        # returns a reduced training set where the only examples remaining are those with a given attribute for the given category
        UnitTestsPlayTennis.test_get_training_set_for_single_attribute(problem)

        # takes a category, attribute, and training set
        # returns a tuple with the attribute name as the first item and a dictionary containing the counts for each class type
        # as the second item
        UnitTestsPlayTennis.test_get_class_type_frequency_for_attribute_tuple(problem)

        # returns a dictionary containing all the counts of all class types for all attributes of the given category
        UnitTestsPlayTennis.test_get_class_type_frequency_dictionary_for_category(problem)

        # returns a dictionary containing the counts for all variables in the given training set
        UnitTestsPlayTennis.test_get_class_type_frequency_dictionary_for_all_categories(problem)

    @staticmethod
    def run_curiosity_tests():
        UnitTestsPlayTennis.test_copy_double_nested_dictionaries()

    # PROBLEM TESTS
    @staticmethod
    def test_calculate_information_gain_for_category(problem):
        pass

    @staticmethod
    def test_calculate_information_gain_for_category_for_undefined_root(problem):

        # I am still a little suspicious of this function. I feel like my margin of error is a little large.
        training_set = problem.get_training_set()
        categories = problem.training_set.get_category_names(training_set)
        expecteds = [0.246, 0.029, 0.151, 0.048]
        error = 0.005

        for i in range(0, len(categories)):
            actual = problem.calculate_information_gain_for_category_for_undefined_root(categories[i], training_set)
            assert UnitTestsPlayTennis.within_acceptable_error(expecteds[i], actual,
                                                               error), 'test_calculate_information_gain_for_category_for_undefined_root() is broken. expected %s got %s' % (
                expecteds[i], actual)

    @staticmethod
    def test_calculate_entropy_for_training_set(problem):

        # value that the training set entropy is supposed to be
        expected_training_set_entropy = 0.940

        # value that the calculate training set entropy actually returned
        actual_training_set_entropy = problem.calculate_entropy_for_training_set(problem.get_training_set())

        # throw an error if they are not the same
        assert expected_training_set_entropy == actual_training_set_entropy, 'calculate_entropy_for_training_set() is broken.\
         expected %s got %s' % (expected_training_set_entropy, actual_training_set_entropy)

    @staticmethod
    def test_calculate_entropy_for_attribute(problem):

        training_set = problem.get_training_set()

        categories = ['Humidity', 'Humidity', 'Wind', 'Wind']
        attributes = ['h', 'n', 'w', 's']
        expecteds = [.985, .591, .811, 1]
        error = 0.005

        for i in range(0, len(categories)):
            actual = problem.calculate_conditional_entropy_for_attribute(categories[i], attributes[i], training_set)
            assert UnitTestsPlayTennis.within_acceptable_error(expecteds[i], actual,
                                                               error), 'calculate_entropy_for_attribute() is broken. expected: %s got: %s' % (
                expecteds[i], actual)

    @staticmethod
    def test_calculate_entropy_for_category(problem):

        outlook_expected_entropy = 0.694
        temp_expected_entropy = 0.911
        humidity_expected_entropy = .789
        wind_expected_entropy = .892

        training_set = problem.get_training_set()

        outlook_actual_entropy = problem.calculate_conditional_entropy_for_category('Outlook', training_set)
        temp_actual_entropy = problem.calculate_conditional_entropy_for_category('Temp', training_set)
        humidity_actual_entropy = problem.calculate_conditional_entropy_for_category('Humidity', training_set)
        wind_actual_entropy = problem.calculate_conditional_entropy_for_category('Wind', training_set)

        assert outlook_expected_entropy > outlook_actual_entropy - 0.2 or \
               outlook_expected_entropy < outlook_actual_entropy + 0.2, 'calculate_entropy_for_category() is broken. expected: %s got: %s' % \
                                                                        (outlook_expected_entropy,
                                                                         outlook_actual_entropy)
        assert temp_expected_entropy > temp_actual_entropy - 0.2 or \
               temp_expected_entropy < temp_actual_entropy + 0.2, 'calculate_entropy_for_category() is broken. expected: %s got: %s' % \
                                                                  (temp_expected_entropy, temp_actual_entropy)
        assert humidity_expected_entropy > humidity_actual_entropy - 0.2 or \
               humidity_expected_entropy < humidity_actual_entropy + 0.2, 'calculate_entropy_for_category() is broken. expected: %s got: %s' % \
                                                                          (humidity_expected_entropy,
                                                                           humidity_actual_entropy)
        assert wind_expected_entropy > wind_actual_entropy - 0.2 or \
               wind_expected_entropy < wind_actual_entropy + 0.2, 'calculate_entropy_for_category() is broken. expected: %s got: %s' % \
                                                                  (wind_expected_entropy, wind_actual_entropy)

    # TRAINING DATA TESTS

    @staticmethod
    def test_get_tokenized_data(problem):
        tokenized_data = problem.get_training_set()
        assert len(tokenized_data[0]) == 6, "improper row length"
        assert len(tokenized_data) == 15, "improper column length"

    @staticmethod
    def test_get_row(problem):
        test_row = ['Day', 'Outlook', 'Temp', 'Humidity', 'Wind', 'PlayTennis']
        assert problem.training_set.get_row(0, problem.get_training_set()) == test_row, 'get_row is broken'

    @staticmethod
    def test_get_column(problem):
        test_column_0 = ['Day', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14']
        assert problem.training_set.get_column(0,
                                               problem.get_training_set()) == test_column_0, 'get_column is broken on column 0'

        test_column_1 = ['Outlook', 's', 's', 'o', 'r', 'r', 'r', 'o', 's', 's', 'r', 's', 'o', 'o', 'r']
        assert problem.training_set.get_column(1,
                                               problem.get_training_set()) == test_column_1, 'get_column is broken on column 1'

        test_column_2 = ['Temp', 'h', 'h', 'h', 'm', 'c', 'c', 'c', 'm', 'c', 'm', 'm', 'm', 'h', 'm']
        assert problem.training_set.get_column(2,
                                               problem.get_training_set()) == test_column_2, 'get_column is broken on column 2'

        test_column_3 = ['Humidity', 'h', 'h', 'h', 'h', 'n', 'n', 'n', 'h', 'n', 'n', 'n', 'h', 'n', 'h']
        assert problem.training_set.get_column(3,
                                               problem.get_training_set()) == test_column_3, 'get_column is broken on column 3'

        test_column_4 = ['Wind', 'w', 's', 'w', 'w', 'w', 's', 's', 'w', 'w', 'w', 's', 's', 'w', 's']
        assert problem.training_set.get_column(4,
                                               problem.get_training_set()) == test_column_4, 'get_column is broken on column 4'

    @staticmethod
    def test_get_category_names(problem):
        test_names = ['Outlook', 'Temp', 'Humidity', 'Wind']
        assert problem.training_set.get_category_names(
            problem.get_training_set()) == test_names, 'get_category_names_is_broken'

    @staticmethod
    def test_get_unique_attributes_for_category(problem):
        test_unique_names_for_outlook = ['s', 'o', 'r']
        test_unique_names_for_temp = ['h', 'm', 'c']
        test_unique_names_for_humidity = ['h', 'n']
        test_unique_names_for_wind = ['w', 's']

        training_set = problem.get_training_set()
        output_for_column_1 = problem.training_set.get_unique_attributes_for_category('Outlook', training_set)
        output_for_column_2 = problem.training_set.get_unique_attributes_for_category('Temp', training_set)
        output_for_column_3 = problem.training_set.get_unique_attributes_for_category('Humidity', training_set)
        output_for_column_4 = problem.training_set.get_unique_attributes_for_category('Wind', training_set)

        assert output_for_column_1 == test_unique_names_for_outlook, 'get_unique attribute names for category broke for outlook'
        assert output_for_column_2 == test_unique_names_for_temp, 'get_unique attribute names for category broke for temp'
        assert output_for_column_3 == test_unique_names_for_humidity, 'get_unique attribute names for category broke for humidity'
        assert output_for_column_4 == test_unique_names_for_wind, 'get_unique attribute names for category broke for wind'

    @staticmethod
    def test_get_unique_attribute_names_from_column(problem):
        test_unique_names_for_outlook = ['s', 'o', 'r']
        test_unique_names_for_temp = ['h', 'm', 'c']
        test_unique_names_for_humidity = ['h', 'n']
        test_unique_names_for_wind = ['w', 's']

        training_set = problem.get_training_set()
        output_for_column_1 = problem.training_set.get_unique_attribute_names_from_column(1, training_set)
        output_for_column_2 = problem.training_set.get_unique_attribute_names_from_column(2, training_set)
        output_for_column_3 = problem.training_set.get_unique_attribute_names_from_column(3, training_set)
        output_for_column_4 = problem.training_set.get_unique_attribute_names_from_column(4, training_set)

        assert output_for_column_1 == test_unique_names_for_outlook, 'get_unique attribute names from column broke for outlook'
        assert output_for_column_2 == test_unique_names_for_temp, 'get_unique attribute names from column broke for temp'
        assert output_for_column_3 == test_unique_names_for_humidity, 'get_unique attribute names from column broke for humidity'
        assert output_for_column_4 == test_unique_names_for_wind, 'get_unique attribute names from column broke for wind'

    @staticmethod
    def test_get_index_of_class_column(problem):
        assert problem.training_set.get_index_of_class_column(
            problem.get_training_set()) == 5, 'get_index_last_data_column() is broken'

    @staticmethod
    def test_get_set_of_unique_class_types(problem):

        # what the set should be
        test_set_of_unique_class_types = ['n', 'y']

        # what the function actually returned
        actual_set_of_unique_class_types = problem.training_set.get_set_of_unique_class_types(
            problem.get_training_set())

        # these sets should be the same and if they are not we have a problem
        assert test_set_of_unique_class_types == actual_set_of_unique_class_types, 'get_set_of_unique_training_types() is broken'

    @staticmethod
    def test_get_category_name_from_column(problem):
        test_name = 'Outlook'
        assert test_name == problem.training_set.get_category_name_from_column(1, problem.get_training_set())

    @staticmethod
    def test_create_attribute_dictionary_from_column(problem):
        test_outlook_dictionary = {'s': {'n': 0, 'y': 0}, 'o': {'n': 0, 'y': 0}, 'r': {'n': 0, 'y': 0}}
        assert test_outlook_dictionary == problem.training_set.create_attribute_dictionary_from_column(1,
                                                                                                       problem.get_training_set())

    @staticmethod
    def test_create_category_tuple_from_column(problem):
        test_category_tuple = ('Wind', {'w': {'n': 0, 'y': 0}, 's': {'n': 0, 'y': 0}})
        assert test_category_tuple == problem.training_set.create_category_tuple_from_column(4,
                                                                                             problem.get_training_set())

    @staticmethod
    def test_create_categories_from_training_set(problem):

        # what the categories dictionary should look like
        test_categories = \
            {
                'Outlook': {'s': {'n': 0, 'y': 0}, 'o': {'n': 0, 'y': 0}, 'r': {'n': 0, 'y': 0}},
                'Temp': {'h': {'n': 0, 'y': 0}, 'm': {'n': 0, 'y': 0}, 'c': {'n': 0, 'y': 0}},
                'Humidity': {'h': {'n': 0, 'y': 0}, 'n': {'n': 0, 'y': 0}},
                'Wind': {'w': {'n': 0, 'y': 0}, 's': {'n': 0, 'y': 0}}
            }

        # what the create_categories_from_training_set() function actually returned
        actual_categories = problem.training_set.create_categories_from_training_set(problem.get_training_set())
        assert test_categories == actual_categories, 'create_categories_from_training_set() is broken'

    @staticmethod
    def test_get_class_values_for_training_set(problem):
        # what the class values should be for this training set
        test_values = ['n', 'n', 'y', 'y', 'y', 'n', 'y', 'n', 'y', 'y', 'y', 'y', 'y', 'n']

        # what the get function actually returned
        actual_values = problem.training_set.get_class_values_for_training_set(problem.get_training_set())

        # throw an error if they are not the same
        assert test_values == actual_values, 'get_class_values_for_training_set() is broken'

    @staticmethod
    def test_get_number_of_training_examples_of_class_type(problem):

        # what the count values should actually be
        test_num_type_yes = 9
        test_num_type_no = 5

        # what the function actually returned
        actual_num_type_yes = problem.training_set.get_number_of_training_examples_of_class_type('y',
                                                                                                 problem.get_training_set())
        actual_num_type_no = problem.training_set.get_number_of_training_examples_of_class_type('n',
                                                                                                problem.get_training_set())

        # throw an error if they are not the same
        assert test_num_type_yes == actual_num_type_yes, 'get_number_of_training_examples_of_class_type() is broken'
        assert test_num_type_no == actual_num_type_no, 'get_number_of_training_examples_of_class_type() is broken'

    @staticmethod
    def test_get_class_type_frequency_dictionary(problem):

        # what the dictionary should actually be
        test_proportion_to_class_type_for_training_set = {'y': 9, 'n': 5}

        # what the function actually returned
        actual_proportion_to_class_type_for_training_set = problem.get_class_type_frequency_dictionary(
            problem.get_training_set())

        # throw an error if they are not the same
        assert test_proportion_to_class_type_for_training_set == actual_proportion_to_class_type_for_training_set, 'get_proportion_to_class_type_for_training_set_dictionary() is broken'

    @staticmethod
    def test_get_number_training_examples(problem):

        # what the value should be
        test_number_of_training_examples = 14

        # what the get function actually returns
        actual_number_of_training_examples = problem.training_set.get_number_training_examples(
            problem.get_training_set())

        # throw an error if they are not the same
        assert test_number_of_training_examples == actual_number_of_training_examples, 'get_number_of_training_examples_is_broken'

    @staticmethod
    def test_has_category(problem):

        training_set = problem.get_training_set()

        # a valid category that exists in the set
        test_valid_category = 'Wind'

        # if the function doesn't report that the category exists in the set throw an exception
        # noinspection SpellCheckingInspection
        assert problem.training_set.has_category(test_valid_category,
                                                 training_set) == True, 'has_category() is broken. It is reporting that a category doesn"t exist in the training set that actually does exist'

        # a invalid category that does not exist in the set
        test_invalid_category = 'DERP'

        # if the function doesn't report that the category does not exist in the set throw an exception
        assert problem.training_set.has_category(test_invalid_category,
                                                 training_set) == False, 'has_category() is broken. It is reporting that a category exists in the training set that actually does not exist'

    @staticmethod
    def test_get_index_of_column_for_category(problem):

        # what the index should be
        # (note: the first category will have index 1, not 0. The first column is for example id)
        index = 1
        # what the function actually returned
        actual_index = problem.training_set.get_index_of_column_for_category('Outlook', problem.get_training_set())
        assert index == actual_index

        # what the index should be
        index = 2
        # what the function actually returned
        actual_index = problem.training_set.get_index_of_column_for_category('Temp', problem.get_training_set())
        assert index == actual_index

        # what the index should be
        index = 3
        # what the function actually returned
        actual_index = problem.training_set.get_index_of_column_for_category('Humidity', problem.get_training_set())
        assert index == actual_index

        # what the index should be
        index = 4
        # what the function actually returned
        actual_index = problem.training_set.get_index_of_column_for_category('Wind', problem.get_training_set())
        assert index == actual_index

    @staticmethod
    def test_get_column_for_category(problem):

        # what column should be returned
        test_column = ['Outlook', 's', 's', 'o', 'r', 'r', 'r', 'o', 's', 's', 'r', 's', 'o', 'o', 'r']

        # what is actually returned
        actual_column = problem.training_set.get_column_for_category('Outlook', problem.get_training_set())

        # throw exception if they are not the same
        assert test_column == actual_column, 'get_column_for_category() is broken'

    @staticmethod
    def test_get_training_set_for_single_attribute(problem):

        # the training set that should be returned
        test_training_set = \
            [
                ['Day', 'Outlook', 'Temp', 'Humidity', 'Wind', 'PlayTennis'],
                ['1', 's', 'h', 'h', 'w', 'n'],
                ['2', 's', 'h', 'h', 's', 'n'],
                ['8', 's', 'm', 'h', 'w', 'n'],
                ['9', 's', 'c', 'n', 'w', 'y'],
                ['11', 's', 'm', 'n', 's', 'y']
            ]

        # the actual set returned by the function
        actual_training_set = problem.training_set.get_training_set_for_single_attribute('Outlook', 's',
                                                                                         problem.get_training_set())

        assert test_training_set == actual_training_set, 'get_training_set_for_single_attribute_is_broken()'

    @staticmethod
    def test_get_class_type_frequency_for_attribute_tuple(problem):

        expected = ('s', {'y': 2, 'n': 3})
        actual = problem.training_set.get_class_type_frequency_for_attribute_tuple('Outlook', 's',
                                                                                   problem.get_training_set())
        assert expected == actual, 'get_class_frequency_for_attribute_tuple() is broken'

        expected = ('o', {'y': 4, 'n': 0})
        actual = problem.training_set.get_class_type_frequency_for_attribute_tuple('Outlook', 'o',
                                                                                   problem.get_training_set())
        assert expected == actual, 'get_class_frequency_for_attribute_tuple() is broken'

        expected = ('r', {'y': 3, 'n': 2})
        actual = problem.training_set.get_class_type_frequency_for_attribute_tuple('Outlook', 'r',
                                                                                   problem.get_training_set())
        assert expected == actual, 'get_class_frequency_for_attribute_tuple() is broken'

    @staticmethod
    def test_get_class_type_frequency_dictionary_for_category(problem):

        expected_attributes_outlook = {'s': {'n': 3, 'y': 2}, 'o': {'n': 0, 'y': 4}, 'r': {'n': 2, 'y': 3}}
        expected_attributes_temp = {'h': {'n': 2, 'y': 2}, 'm': {'n': 2, 'y': 4}, 'c': {'n': 1, 'y': 3}}
        expected_attributes_humidity = {'h': {'n': 4, 'y': 3}, 'n': {'n': 1, 'y': 6}}
        expected_attributes_wind = {'w': {'n': 2, 'y': 6}, 's': {'n': 3, 'y': 3}}

        training_set = problem.get_training_set()

        actual_attributes_outlook = problem.training_set.get_class_type_frequency_dictionary_for_category('Outlook',
                                                                                                          training_set)
        actual_attributes_temp = problem.training_set.get_class_type_frequency_dictionary_for_category('Temp',
                                                                                                       training_set)
        actual_attributes_humidity = problem.training_set.get_class_type_frequency_dictionary_for_category('Humidity',
                                                                                                           training_set)
        actual_attributes_wind = problem.training_set.get_class_type_frequency_dictionary_for_category('Wind',
                                                                                                       training_set)

        assert expected_attributes_outlook == actual_attributes_outlook, 'test_get_class_tye_frequency_dictionary() is broken'
        assert expected_attributes_temp == actual_attributes_temp, 'test_get_class_tye_frequency_dictionary() is broken'
        assert expected_attributes_humidity == actual_attributes_humidity, 'test_get_class_tye_frequency_dictionary() is broken'
        assert expected_attributes_wind == actual_attributes_wind, 'test_get_class_tye_frequency_dictionary() is broken'

    @staticmethod
    def test_get_class_type_frequency_dictionary_for_all_categories(problem):

        expected_dictionary = \
            {
                'Outlook': {'s': {'n': 3, 'y': 2}, 'o': {'n': 0, 'y': 4}, 'r': {'n': 2, 'y': 3}},
                'Temp': {'h': {'n': 2, 'y': 2}, 'm': {'n': 2, 'y': 4}, 'c': {'n': 1, 'y': 3}},
                'Humidity': {'h': {'n': 4, 'y': 3}, 'n': {'n': 1, 'y': 6}},
                'Wind': {'w': {'n': 2, 'y': 6}, 's': {'n': 3, 'y': 3}}
            }

        actual_dictionary = problem.training_set.get_class_type_frequency_dictionary_for_all_categories(
            problem.get_training_set())

        assert expected_dictionary == actual_dictionary, 'test_get_class_type_frequency_dictionary_for_all_categories() is broken'

    # CURIOSITY TESTS
    @staticmethod
    def test_copy_double_nested_dictionaries():

        test_attributes_outlook = {'s': {'n': 3, 'y': 2}, 'o': {'n': 0, 'y': 4}, 'r': {'n': 2, 'y': 3}}
        test_attributes_temp = {'h': {'n': 2, 'y': 2}, 'm': {'n': 2, 'y': 4}, 'c': {'n': 1, 'y': 3}}
        test_attributes_humidity = {'h': {'n': 4, 'y': 3}, 'n': {'n': 1, 'y': 6}}
        test_attributes_wind = {'w': {'n': 2, 'y': 6}, 's': {'n': 3, 'y': 3}}

        test_categories = {'Outlook': test_attributes_outlook, 'Temp': test_attributes_temp,
                           'Humidity': test_attributes_humidity, 'Wind': test_attributes_wind}

        # so, now we are going to do a deep copy, and then alter the second one.  If they are not equal, then we have correctly done a deep copy and passed the test
        copy_test_categories = copy.deepcopy(test_categories)

        # renames the key "Outlook" to be "new_key"
        copy_test_categories['new_key'] = copy_test_categories.pop('Outlook')

        # these two separate dictionaries should not be the same, if they are it means they share the same memory space and we have a problem because we have not truly made a deep copy
        assert copy_test_categories != test_categories, 'there was a problem making a deep copy of the double nested dictionary'

    @staticmethod
    def within_acceptable_error(expected, actual, error):
        return abs(expected - actual) <= error

    @staticmethod
    def abs(value):
        if value < 0:
            return -value
        else:
            return value

    @staticmethod
    def test_precision(problem):

        expected = 1.235  # it would be 1.234 but it's going to round up if Context.rounding = ROUND_HALF_EVEN
        actual = problem.precision(1.23456789)
        assert expected == actual, 'precision() is broken. expected: %s got: %s' % (expected, actual)

    @staticmethod
    def test_create_decision_tree(problem):
        training_set = problem.get_training_set()
        problem.create_decision_tree(training_set)

    @staticmethod
    def test_get_node_string(problem):

        training_set = problem.get_training_set()

        test_parent_node_none = None
        none_expected = 'none'
        none_actual = problem.get_node_string(test_parent_node_none)
        assert none_expected == none_actual, 'get_node_string() is broken. expected: %s got: %s' % (
            none_expected, none_actual)

        test_parent_node_some_category = Node('some category', 0.00, None, training_set, False, None)
        some_category_expected = 'some category'
        some_category_actual = problem.get_node_string(test_parent_node_some_category)
        assert some_category_expected == some_category_actual, 'get_node_string() is broken. expected: %s got: %s' % (
            some_category_expected, some_category_actual)

    # DECISION TREE TESTS

    @staticmethod
    def test_get_child_nodes_of():

        test_tree = UnitTestsPlayTennis.create_simple_test_tree()

        # test_tree.print_me()
        # problem.decision_tree.print_me()

        # so now when we test this function on the root node we should get child 1, 2, and 3 back
        actual_child_nodes_of_root = test_tree.get_child_nodes_of(test_tree.root)

        # print("actual: " + str(actual_child_nodes_of_root))
        # for item in actual_child_nodes_of_root:
        #    print item.category + " ",

        expected_child_nodes = UnitTestsPlayTennis.create_expected_child_nodes_for_root_for_simple_test_tree()

        # check that each expected child is actually returned by the function
        # this will throw an exception if we do not break out of the loop when we found the proper child
        for expected in expected_child_nodes:
            for actual in actual_child_nodes_of_root:
                if actual.category == expected.category:
                    # we found the expected child node
                    break
            else:
                # we did not find the expected child node
                assert 'get_child_nodes_of() is broken. expected: %s but it was not returned' % str(expected.category)

    @staticmethod
    def test_get_level_depth_for_node():

        # simple test for testing the depth of the root
        test_tree = UnitTestsPlayTennis.create_simple_test_tree()

        expected_root_level = 0
        root_node = test_tree.get_node_with_category('root')
        actual_root_level = test_tree.get_level_depth_for_node(root_node)
        assert (
            expected_root_level == actual_root_level), 'get_level depth_for_node() is broken. expected %s got %s' % (
            expected_root_level, actual_root_level)

        # here we're going to test level depth retrieval for lower levels
        two_level_test_tree = UnitTestsPlayTennis.create_two_level_test_tree()

        expected_child1_level = 1
        child1 = two_level_test_tree.get_node_with_category('child1')
        actual_child1_level = two_level_test_tree.get_level_depth_for_node(child1)
        assert expected_child1_level == actual_child1_level, 'get_level depth_for_node() is broken. expected %s got %s' % (
            expected_child1_level, actual_child1_level)

        # test for child4 on level 2
        expected_child4_level = 2
        child4 = two_level_test_tree.get_node_with_category('child4')
        actual_child4_level = two_level_test_tree.get_level_depth_for_node(child4)
        assert expected_child4_level == actual_child4_level, 'get_level_depth_for_node() is broken. expected %s got %s' % (
            expected_child4_level, actual_child4_level)

    @staticmethod
    def test_get_deepest_level():

        expected = 2
        two_level_test_tree = UnitTestsPlayTennis.create_two_level_test_tree()
        actual = two_level_test_tree.get_deepest_level()
        assert expected == actual, 'get_deepest_level() is broken. expected %s got %s' % (expected, actual)

    @staticmethod
    def test_got_correct_decision_tree(problem):

        # todo: write this if you have time and/or you're feeling ambitious
        pass

    @staticmethod
    def create_simple_test_tree():

        # test tree
        test_tree = DecisionTree()

        # make nodes for test tree
        root = Node('root', 0, None, [], False, None)
        test_tree.add_node(root)

        # level 1

        child1 = Node('child1', 0, root, [], False, None)
        child2 = Node('child2', 0, root, [], False, None)
        child3 = Node('child3', 0, root, [], False, None)

        test_tree.add_node(child1)
        test_tree.add_node(child2)
        test_tree.add_node(child3)

        return test_tree

    @staticmethod
    def create_expected_child_nodes_for_root_for_simple_test_tree():
        expected_child_nodes = []
        root = Node('root', 0, None, [], False, None)
        child1 = Node('child1', 0, root, [], False, None)
        child2 = Node('child2', 0, root, [], False, None)
        child3 = Node('child3', 0, root, [], False, None)
        expected_child_nodes.append(child1)
        expected_child_nodes.append(child2)
        expected_child_nodes.append(child3)
        return expected_child_nodes

    @staticmethod
    def create_two_level_test_tree():

        # test tree
        two_level_test_tree = DecisionTree()

        # make nodes for test tree
        root = Node('root', 0, None, [], False, None)
        two_level_test_tree.add_node(root)

        # level 1

        child1 = Node('child1', 0, two_level_test_tree.root, [], False, None)
        child2 = Node('child2', 0, two_level_test_tree.root, [], False, None)
        child3 = Node('child3', 0, two_level_test_tree.root, [], False, None)

        two_level_test_tree.add_node(child1)
        two_level_test_tree.add_node(child2)
        two_level_test_tree.add_node(child3)

        # level 2
        child3 = two_level_test_tree.get_node_with_category(child3.category)
        child4 = Node('child4', 0, child3, [], False, None)
        child5 = Node('child5', 0, child3, [], False, None)
        child6 = Node('child6', 0, child3, [], False, None)

        two_level_test_tree.add_node(child4)
        two_level_test_tree.add_node(child5)
        two_level_test_tree.add_node(child6)

        return two_level_test_tree
