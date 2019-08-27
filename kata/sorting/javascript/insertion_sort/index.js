

/*

 Insertion sort is a simple sorting algorithm that builds the final sorted array (or list) one item at a time. It is
 much less efficient on large lists than more advanced algorithms such as quicksort, heapsort, or merge sort. However,
 insertion sort provides several advantages:
 Simple implementation: Bentley shows a three-line C version, and a five-line optimized version
 Efficient for (quite) small data sets, much like other quadratic sorting algorithms
 More efficient in practice than most other simple quadratic (i.e., O(n2)) algorithms such as selection sort or bubble
 sort
 Adaptive, i.e., efficient for data sets that are already substantially sorted: the time complexity is O(nk) when each
  element in the input is no more than k places away from its sorted position
 Stable; i.e., does not change the relative order of elements with equal keys
 In-place; i.e., only requires a constant amount O(1) of additional memory space
 Online; i.e., can sort a list as it receives it
 When people manually sort cards in a bridge hand, most use a method that is similar to insertion sort

 */

(function(){

    var original_set = [];

//populate the original set with 10 random numbers between 1 and 10
    for(var i = 0, highest_random_number = 9; i < highest_random_number; i++){
        original_set.push(Math.round(Math.random() * highest_random_number))
    }

// get the sorted set
    var sorted_set = insertion_sort(original_set);

    console.log("\n");
    console.log("original set: [" + original_set.toString() + "]");
    console.log("sorted set:   [" + sorted_set.toString() + "]");


    function insertion_sort(input_set){

        temp_set = deepcopy(input_set);

        /*

             we start at 1 and not zero because the first element is skipped
             intuitively, this is because, what would we compare the first element to anyway?
             so we start at the second element and compare it to the first element

             I have chosen to call this the frontier_index, because the frontier keeps moving forward as the set of
             elements behind it is sorted.  All set data after the frontier index is yet to be sorted
        
         */
        var current_index;
        for(var frontier_index = 0; frontier_index < input_set.length; frontier_index++){

            console.log(temp_set);

            current_index = frontier_index;

            // until we are at the beginning of the set, swap the offending item down until it is where it belongs
            while(current_index > 0 && temp_set[current_index - 1] > temp_set[current_index]){
                console.log("\tswap(" + temp_set[current_index - 1].toString() + ", " + temp_set[current_index].toString() + ")");

                temp_set = swap(temp_set, current_index - 1, current_index);
                current_index -= 1
            }

        }

        return temp_set;

    }

    function swap(input_set, first_index, second_index){
        var temp_set = deepcopy(input_set);
        first_item = temp_set[first_index];
        second_item = temp_set[second_index];

        temp_set[first_index] = second_item;
        temp_set[second_index] = first_item;

        return temp_set;
    }

    function deepcopy(input_set){
        var temp_set = [];

        for(var i = 0; i < input_set.length; i++){

            temp_set.push(input_set[i]);

        }
        return temp_set;
    }

})();



