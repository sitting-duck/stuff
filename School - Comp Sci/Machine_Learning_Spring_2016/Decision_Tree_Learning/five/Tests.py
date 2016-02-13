from Info_Math import Info_Math


class Tests:

    expected_tree = []

    def __init__(self):
        pass

    def get_final_tree_test_data_from_file(self, problem):

        file = open('expected_tree_my_format.txt', 'r')

        self.expected_tree = list(file)

    def test_tree_for_equality(self, test_tree):

        if True:
            return

        if test_tree == []:
            return

        for i in range(0, len(test_tree)):
            print '',
            assert self.expected_tree[i] == test_tree[i], 'failure: expected: %s got: %s for line %i \ntest_tree: %s' % (self.expected_tree[i], test_tree[i], i, str(test_tree))

    def run_tests(self, problem):
        self.test_calculate_entropy_for_training_set(problem)

    def test_calculate_entropy_for_training_set(self, problem):

        training_set = problem.training_data.get_training_set('./testing/set_entropy_should_be_one.dat')

        entropy = Info_Math.calculate_entropy_for_training_set(training_set)

        assert entropy == 1, "error on calculate entropy for training_set()"