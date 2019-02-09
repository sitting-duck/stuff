import copy
import random

__author__ = "Ashley Tharp"


def main():
    """
    In computer science, selection sort is a sorting algorithm, specifically an in-place comparison sort. It has O(n2)
     time complexity, making it inefficient on large lists, and generally performs worse than the similar insertion
     sort. Selection sort is noted for its simplicity, and it has performance advantages over more complicated
     algorithms in certain situations, particularly where auxiliary memory is limited.

    The algorithm divides the input list into two parts: the sublist of items already sorted, which is built up from
    left to right at the front (left) of the list, and the sublist of items remaining to be sorted that occupy the rest
    of the list. Initially, the sorted sublist is empty and the unsorted sublist is the entire input list. The
    algorithm proceeds by finding the smallest (or largest, depending on sorting order) element in the unsorted sublist,
     exchanging (swapping) it with the leftmost unsorted element (putting it in sorted order), and moving the sublist
     boundaries one element to the right.

    Here is an example of this sort algorithm sorting five elements:

    64 25 12 22 11 // this is the initial, starting state of the array

    11 25 12 22 64 // sorted sublist = {11}

    11 12 25 22 64 // sorted sublist = {11, 12}

    11 12 22 25 64 // sorted sublist = {11, 12, 22}

    11 12 22 25 64 // sorted sublist = {11, 12, 22, 25}

    11 12 22 25 64 // sorted sublist = {11, 12, 22, 25, 64}

    """
    original_set = random.sample(range(1, 11), 10)

    sorted_set = selection_sort(original_set)

    print "\n"

    print "original set: " + str(original_set)

    print "sorted_set:   " + str(sorted_set)


def selection_sort(input_set):

    temp_set = copy.deepcopy(input_set)

    for frontier_index in range(0, len(input_set) - 1):

        print str(temp_set)

        # assume the current minimum element is the one at the end of the frontier
        current_min_index = frontier_index

        # test against the elements after the frontier to find the actual next smallest
        for current_index in range(frontier_index + 1, len(input_set)):
            if temp_set[current_index] < temp_set[current_min_index]:
                # found a new minimum so let's remember its index
                current_min_index = current_index

        if current_min_index != frontier_index:
            temp_set = swap(temp_set, frontier_index, current_min_index)
            print "\tswap(" + str(temp_set[frontier_index]) + ", " + str(temp_set[current_index]) + ")"

    return temp_set


def swap(input_set, first_index, second_index):
    temp_set = copy.deepcopy(input_set)
    first_item = copy.deepcopy(temp_set[first_index])
    second_item = copy.deepcopy(temp_set[second_index])

    temp_set[first_index] = second_item
    temp_set[second_index] = first_item

    return temp_set


if __name__ == '__main__':
    main()
