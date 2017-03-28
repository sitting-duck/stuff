import copy

from utils.ParseTools import ParseTools


class Classify:

    def __init__(self):
        pass

    @staticmethod
    def get_accuracy(decision_tree, example_set):

        # a tree without a root is not actually a tree at all, so accuracy must be zero
        if decision_tree.has_root() is False:
            return 0.0

        num_examples = len(example_set) - 1
        num_correct = 0
        current_node = decision_tree.root
        # get rid of the line with the category tags
        temp_set = copy.deepcopy(example_set)
        del temp_set[0]

        for current_example in temp_set:

            # traverse down the tree
            while True:

                if current_node.is_leaf:
                    if current_node.category == current_example[-1]:
                        num_correct += 1
                    # start at the beginning of the tree again for the next example
                    current_node = decision_tree.root
                    break

                current_category = current_node.category
                current_category_index = ParseTools.get_index_of_column_for_category(current_category, example_set)
                # print current_category_index
                # print "ex: " + str(current_example)
                current_attribute = current_example[current_category_index]
                new_current_node = decision_tree.get_node_with(current_node, current_attribute)
                new_current_category = new_current_node.category
                current_node = new_current_node

        return float(float(num_correct) / float(num_examples)) * 100.0
