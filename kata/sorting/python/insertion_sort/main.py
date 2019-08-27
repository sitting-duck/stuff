import copy

__author__ = "Ashley Tharp"

import random

def main():
    """

    Insertion sort is a simple sorting algorithm that builds the final sorted array (or list) one item at a time. It is much less efficient on large lists than more advanced algorithms such as quicksort, heapsort, or merge sort. However, insertion sort provides several advantages:

    Simple implementation: Bentley shows a three-line C version, and a five-line optimized version[1]:116
    Efficient for (quite) small data sets, much like other quadratic sorting algorithms
    More efficient in practice than most other simple quadratic (i.e., O(n2)) algorithms such as selection sort or bubble sort
    Adaptive, i.e., efficient for data sets that are already substantially sorted: the time complexity is O(nk) when each element in the input is no more than k places away from its sorted position
    Stable; i.e., does not change the relative order of elements with equal keys
    In-place; i.e., only requires a constant amount O(1) of additional memory space
    Online; i.e., can sort a list as it receives it

    When people manually sort cards in a bridge hand, most use a method that is similar to insertion sort

    """

    original_set = random.sample(range(1, 11), 10)

    sorted_set = insertion_sort(original_set)

    print "\n"

    print "original set: " + str(original_set)

    print "sorted_set:   " + str(sorted_set)

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