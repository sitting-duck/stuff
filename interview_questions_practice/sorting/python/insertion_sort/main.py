import copy

__author__ = "Ashley Tharp"

import random

def main():

    original_set = random.sample(range(1, 11), 10)

    sorted_set = insertion_sort(original_set)

    print "\n"

    print "original set: " + str(original_set)

    print "sorted_set: " + str(sorted_set)


def insertion_sort(set, comparator = None):
    # this function assumes that arrays are zero based

    temp_set = copy.deepcopy(set)

    # we start at 1 and not zero because the first element is skipped
    # intuitively, this is because, what would we compare the first element to anyway?
    # so we start at the second element and compare it to the first element

    # I have chosen to call this the frontier_index, because the frontier keeps moving forward as the set of elements
    # behind it is sorted.  All set data after the frontier index is yet to be sorted
    for frontier_index in range(1, len(set)):

        print str(temp_set)

        current_index = frontier_index

        # until we are at the beginning of the set, swap the offending item down until it is where it belongs
        while current_index > 0 and temp_set[current_index - 1] > temp_set[current_index]:
            print "\tswap(" + str(temp_set[current_index - 1]) + ", " + str(temp_set[current_index]) + ")"

            temp_set = swap(temp_set, current_index - 1, current_index)
            current_index -= 1

    return temp_set


def swap(input_set, first_index, second_index):
    temp_set = copy.deepcopy(input_set)
    first_item = copy.deepcopy(temp_set[first_index])
    second_item = copy.deepcopy(temp_set[second_index])

    temp_set[first_index] = second_item
    temp_set[second_index] = first_item

    return temp_set


def test_swap():

    test_set = [1, 2, 3]
    expected_set = [3, 2, 1]

    actual_set = swap(test_set, 0, 2)

    assert expected_set == actual_set, 'swap is broken'

if __name__ == "__main__":
    test_swap()
    main()