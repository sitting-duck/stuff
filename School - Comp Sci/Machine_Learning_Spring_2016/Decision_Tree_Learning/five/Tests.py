
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
            assert self.expected_tree[i] == test_tree[i], 'failure: expected: %s got: %s for line %i \ntest_tree: %s' % (self.expected_tree[i], test_tree[i], i, str(test_tree))

    @staticmethod
    def run_tests(problem):
        Tests.test_email_entropy_root(problem)

        Tests.test_email_gain_root_nigeria(problem)
        Tests.test_email_gain_root_viagra(problem)
        Tests.test_email_gain_root_learning(problem)

        Tests.test_email_gain_root_nigeria_equal_zero(problem)

        Tests.test_create_decision_tree_until_email_gain_root_nigeria_equal_zero(problem)


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