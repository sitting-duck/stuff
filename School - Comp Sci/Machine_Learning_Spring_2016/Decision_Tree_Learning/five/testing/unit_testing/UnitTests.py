import sys
from utils.InfoMath import InfoMath
from utils.ParseTools import ParseTools


class UnitTests:
    expected_tree = []

    def __init__(self):
        self.expected_tree = self.get_final_tree_test_data_from_file(sys.argv[2])

    # this function collects the correct final decision tree from a file that we will use to make sure we have generated
    # correct decision tree from the data
    @staticmethod
    def get_final_tree_test_data_from_file(file_path_to_expected_tree):
        expected_test_tree_file = open(file_path_to_expected_tree, 'r')

        return list(expected_test_tree_file)

    def test_tree_for_equality(self, test_tree):

        if True:
            return

        for i in range(0, len(test_tree)):
            # we call split so that we don't run into problems with tabs versus spaces
            assert self.expected_tree[i].split() == test_tree[i].split(), 'failure: expected: %s got: %s for line %i\
             \ntest_tree: %s' % (self.expected_tree[i], test_tree[i], i, str(test_tree))

    @staticmethod
    def run_tests(problem):
        UnitTests.test_single_class_type(problem)
        UnitTests.test_is_pure(problem)
        UnitTests.test_is_split_equally_between_class_types(problem)
        UnitTests.test_is_leaf(problem)

        UnitTests.test_email_entropy_root(problem)

        UnitTests.test_email_gain_root_nigeria(problem)
        UnitTests.test_email_gain_root_viagra(problem)
        UnitTests.test_email_gain_root_learning(problem)

        UnitTests.test_email_gain_root_nigeria_equal_zero(problem)

    @staticmethod
    def test_is_leaf(problem):
        # a node is a leaf if
        # a. the training set is pure

        # note: a node does not have to be pure to be a leaf,
        # it can be a leaf AND impure if there are zero categories left and there is more than one class type
        training_set = problem.training_data.get_training_set(
            './testing/unit_testing/purity/training_examples_equally_split_between_two_classes.dat')
        expected_result = True
        result = ParseTools.is_leaf(training_set)
        assert expected_result == result, 'error on test_is_leaf() expected %s got %s' % (expected_result, result)

        training_set = problem.training_data.get_training_set('./testing/unit_testing/purity/no_training_examples_no_categories.dat')
        expected_result = True
        result = ParseTools.is_leaf(training_set)
        assert expected_result == result, 'error on test_is_leaf() expected %s got %s' % (expected_result, result)

    @staticmethod
    def test_is_split_equally_between_class_types(problem):
        training_set = problem.training_data.get_training_set(
            './testing/unit_testing/purity/training_examples_equally_split_between_two_classes.dat')
        expected_result = True
        result = ParseTools.is_split_equally_between_class_types(training_set)
        assert expected_result == result, 'error on training_examples_equally_split_between_two_classes expected %s got %s' % (
            expected_result, result)

        training_set = problem.training_data.get_training_set(
            './testing/unit_testing/purity/training_examples_not_equally_split_between_two_classes.dat')
        expected_result = False
        result = ParseTools.is_split_equally_between_class_types(training_set)
        assert expected_result == result, 'error on training_examples_not_equally_split_between_two_classes expected %s got %s' % (
            expected_result, result)

    @staticmethod
    def test_is_pure(problem):
        expected_result = True

        training_set = problem.training_data.get_training_set(
            './testing/unit_testing/purity/should_be_pure_no_training_examples_one_category.dat')
        result = ParseTools.is_pure(training_set)
        assert expected_result == result, 'error on test_is_pure() expected %s got %s' % (expected_result, result)

        training_set = problem.training_data.get_training_set(
            './testing/unit_testing/purity/should_be_pure_no_training_examples_two_categories.dat')
        result = ParseTools.is_pure(training_set)
        assert expected_result == result, 'error on test_is_pure() expected %s got %s' % (expected_result, result)

    @staticmethod
    def test_single_class_type(problem):
        training_set = problem.training_data.get_training_set('./testing/unit_testing/purity/single_class_type.dat')
        result = ParseTools.is_single_class_type(training_set)
        expected_result = True
        assert result == expected_result, 'error on test_single_class_type() expected %s got %s' % \
                                          (expected_result, result)

        training_set = problem.training_data.get_training_set('./testing/unit_testing/purity/non_single_class_type.dat')
        result = ParseTools.is_single_class_type(training_set)
        expected_result = False
        assert result == expected_result, 'error on test_single_class_type() expected %s got %s' % \
                                          (expected_result, result)

    @staticmethod
    def test_email_entropy_root(problem):
        training_set = problem.training_data.get_training_set('./testing/unit_testing/email/set_entropy_should_be_one.dat')

        entropy = InfoMath.calculate_entropy_for_training_set(training_set)

        assert entropy == 1, "error on calculate entropy for training_set()"

    @staticmethod
    def test_email_gain_root_nigeria(problem):
        training_set = problem.training_data.get_training_set('./training/email/email.dat')

        gain_root_nigeria = InfoMath.calculate_information_gain_for_category('nigeria', None, None, training_set)
        expected_gain = 0.278

        assert InfoMath.precision(gain_root_nigeria) == expected_gain, 'error on test_email_gain_root_nigeria() expected \
        %s got %s' % (expected_gain, gain_root_nigeria)

    @staticmethod
    def test_email_gain_root_viagra(problem):
        training_set = problem.training_data.get_training_set('./training/email/email.dat')

        gain_root_viagra = InfoMath.calculate_information_gain_for_category('viagra', None, None, training_set)
        expected_gain = 0.035

        assert InfoMath.precision(gain_root_viagra) == expected_gain, 'error on test_email_gain_root_viagra() expected \
        %s got %s' % (gain_root_viagra, expected_gain)

    @staticmethod
    def test_email_gain_root_learning(problem):
        training_set = problem.training_data.get_training_set('./training/email/email.dat')

        gain_root_learning = InfoMath.calculate_information_gain_for_category('learning', None, None, training_set)
        expected_gain = 0.236

        assert InfoMath.precision(gain_root_learning) == expected_gain, 'error on test_email_gain_root_learning() expected\
         %s got %s' % (gain_root_learning, expected_gain)

    @staticmethod
    def test_email_gain_root_nigeria_equal_zero(problem):
        training_set = problem.training_data.get_training_set('./training/email/email.dat')

        reduced_training_set_nigeria_zero = ParseTools.get_reduced_training_set('nigeria', '0', training_set)

        gain_root_nigeria_equal_zero = InfoMath.calculate_conditional_entropy_for_attribute('nigeria', '0',
                                                                                            reduced_training_set_nigeria_zero)

        expected_gain_root_nigeria_equal_zero = 0.722

        assert InfoMath.precision(gain_root_nigeria_equal_zero) == expected_gain_root_nigeria_equal_zero, 'error on \
        test_email_gain_root_nigeria_equal_zero() expected %s got %s' % (
            expected_gain_root_nigeria_equal_zero, gain_root_nigeria_equal_zero)
