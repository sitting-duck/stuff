
class Tests:

    expected_tree = []

    def __init_(self):
        pass

    def get_test_data_from_file(self, problem):

        file = open('expected_tree_my_format.txt', 'r')

        self.expected_tree = list(file)

    def test_tree_for_equality(self, test_tree):

        #if True:
        #    return

        if test_tree == []:
            return

        for i in range(0, len(test_tree)):
            print '',
            assert self.expected_tree[i] == test_tree[i], 'failure: expected: %s got: %s for line %i \ntest_tree: %s' % (self.expected_tree[i], test_tree[i], i, str(test_tree))