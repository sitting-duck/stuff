
import sys
from Info_Math import Info_Math
from Training_Data import Training_Data


class Tests:

    expected_tree = []

    def __init__(self):

        self.expected_tree = self.get_final_tree_test_data_from_file(sys.argv[2])

    @staticmethod
    def get_final_tree_test_data_from_file(file_path_to_expected_tree):

        file = open(file_path_to_expected_tree, 'r')

        return list(file)

    def test_tree_for_equality(self, test_tree):

        if True:
            return

        if test_tree == []:
            return

        for i in range(0, len(test_tree)):
            print '',
            #we call split so that we don't run into problems with tabs versus spaces
            assert self.expected_tree[i].split() == test_tree[i].split(), 'failure: expected: %s got: %s for line %i \ntest_tree: %s' % (self.expected_tree[i], test_tree[i], i, str(test_tree))

    @staticmethod
    def run_tests(problem):

        Tests.test_single_class_type(problem)
        Tests.test_is_pure(problem)
        Tests.test_is_leaf(problem)

        Tests.test_email_entropy_root(problem)

        Tests.test_email_gain_root_nigeria(problem)
        Tests.test_email_gain_root_viagra(problem)
        Tests.test_email_gain_root_learning(problem)

        Tests.test_email_gain_root_nigeria_equal_zero(problem)

        Tests.test_create_decision_tree_until_email_gain_root_nigeria_equal_zero(problem)

    @staticmethod
    def test_is_leaf(problem):

        #note: a node does not have to be pure to be a leaf,
        #it can be impure if there are zero categories left and there is more than one class type
        #or it can also be impure if there are multiple categories left

        #a node is a leaf if
        # a. the training set is pure

        # select the most common type in the local training set
        # when  the training set is not pure but there are no categories left and there is more than zero examples

        #select the most common type in the global training set
        # when the training set has zero training examples



        pass

    @staticmethod
    def test_is_pure(problem):

        expected_result = True

        training_set = problem.training_data.get_training_set('./testing/purity/should_be_pure_no_training_examples_one_category.dat')
        result = Training_Data.is_pure(training_set)
        assert expected_result == result, 'error on test_is_pure() expected %s got %s' % (expected_result, result)

        training_set = problem.training_data.get_training_set('./testing/purity/should_be_pure_no_training_examples_two_categories.dat')
        result = Training_Data.is_pure(training_set)
        assert expected_result == result, 'error on test_is_pure() expected %s got %s' % (expected_result, result)

        training_set = problem.training_data.get_training_set('./testing/purity/should_be_pure_training_examples_equally_split_between_two_classes.dat')
        result = Training_Data.is_pure(training_set)
        assert expected_result == result, 'error on test_is_pure() expected %s got %s' % (expected_result, result)

    @staticmethod
    def test_single_class_type(problem):

        training_set = problem.training_data.get_training_set('./testing/purity/single_class_type.dat')
        result = Training_Data.is_single_class_type(training_set)
        expected_result = True
        assert result == expected_result, 'error on test_single_class_type() expected %s got %s' % (expected_result, result)

        training_set = problem.training_data.get_training_set('./testing/purity/non_single_class_type.dat')
        result = Training_Data.is_single_class_type(training_set)
        expected_result = False
        assert result == expected_result, 'error on test_single_class_type() expected %s got %s' % (expected_result, result)

    @staticmethod
    def test_email_entropy_root(problem):

        training_set = problem.training_data.get_training_set('./testing/set_entropy_should_be_one.dat')

        entropy = Info_Math.calculate_entropy_for_training_set(training_set)

        assert entropy == 1, "error on calculate entropy for training_set()"

    @staticmethod
    def test_email_gain_root_nigeria(problem):

        training_set = problem.training_data.get_training_set('./testing/email.dat')

        gain_root_nigeria = Info_Math.calculate_information_gain_for_category('nigeria', None, None, training_set)
        expected_gain = 0.278

        assert gain_root_nigeria == expected_gain, 'error on test_email_gain_root_nigeria() expected %s got %s' % (expected_gain, gain_root_nigeria)

    @staticmethod
    def test_email_gain_root_viagra(problem):

        training_set = problem.training_data.get_training_set('./testing/email.dat')

        gain_root_viagra = Info_Math.calculate_information_gain_for_category('viagra', None, None, training_set)
        expected_gain = 0.035

        assert gain_root_viagra == expected_gain, 'error on test_email_gain_root_viagra() expected %s got %s' % (gain_root_viagra, expected_gain)

    @staticmethod
    def test_email_gain_root_learning(problem):

        training_set = problem.training_data.get_training_set('./testing/email.dat')

        gain_root_learning = Info_Math.calculate_information_gain_for_category('learning', None, None, training_set)
        expected_gain = 0.236

        assert gain_root_learning == expected_gain, 'error on test_email_gain_root_learning() expected %s got %s' % (gain_root_learning, expected_gain)

    @staticmethod
    def test_email_gain_root_nigeria_equal_zero(problem):
        #todo: throw in type checks into calc functions to make sure we are passing strings and not ints

        training_set = problem.training_data.get_training_set('./testing/email.dat')

        reduced_training_set_nigeria_zero = Training_Data.get_reduced_training_set('nigeria', '0', training_set)

        gain_root_nigeria_equal_zero = Info_Math.calculate_conditional_entropy_for_attribute('nigeria', '0', training_set)

        expected_gain_root_nigeria_equal_zero = 0.722

        assert gain_root_nigeria_equal_zero == expected_gain_root_nigeria_equal_zero, 'error on test_email_gain_root_nigeria_equal_zero() expected %s got %s' % (expected_gain_root_nigeria_equal_zero, gain_root_nigeria_equal_zero)

        print '',


    @staticmethod
    def test_create_decision_tree_until_email_gain_root_nigeria_equal_zero(problem):
        pass