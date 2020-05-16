package sortJavaApplication;

import java.util.Scanner;

/**
 * This class contains the driver class and the methods for BINARYTREESORT,
 * BUBBLESORT, HEAPSORT, MERGESORT, and QUICKSORT
 * 
 * 
 * @version 1.0
 *
 */
public class Main {

	//scanner object for user input
	private static Scanner scanner = new Scanner( System.in );
	
	/**
	 * The main program; no parameters needed
	 * 	  
	 * @param args An array of strings that contains the command line argument.
	 */
	public static void main(String[] args)
	{
		//integer size of the array
		int size;
		
		
		System.out.println("Enter the number of values to sort between 10 and 20.");
		String input = scanner.nextLine(); //get size of array from user
	
		size = Integer.parseInt( input );  // converts a String into an int value

        while(size < 10 || size > 20) {
            System.out.println("Error: Please enter a value between 10 and 20");
            input = scanner.nextLine();
            size = Integer.parseInt(input);
        }
		
		//integer array of values to be sorted
		int[] numArray = new int[size];
		
		//for loop to take values and enter them into the array
		for(int i = 0; i < size; i++)
		{
			System.out.println("Enter an integer value into the array");
			input = scanner.nextLine(); //get size of array from user
			numArray[i] = Integer.parseInt( input );
		}
	
		System.out.println("\nThis is the array of values");
		for(int i = 0; i < size; i++)
		{
			System.out.println(i);
		}
		
		System.out.println("\nStart the Binary Tree Sort");
		BinaryTreeSort(numArray, size);
		
		System.out.println("Binary Tree Sort is complete");
	

	
	
	//mySorts.BubbleSort(numArray, size);
	
	//mySorts.HeapSort(numArray, size);
	
	//mySorts.BinaryTreeSort(numArray, size);
	
	//mySorts.MergeSort(numArray, size);
	
	//mySorts.QuickSort(numArray, size);
	
	}
	
	/**
	 * This method conducts the BinaryTreeSort Method
	 * 
	 * @param items
	 * @param size
	 */
	public static void BinaryTreeSort(int[] items, int size)
	{
		Node root = null;
        Main j = new Main();
		
		for(int i = 0; i < size; i++)
		{
			Main.Node n = j.new Node(items[i]);
			if (root == null)
			{
				root = n;
			}
			else 
				insert(n, root);
			}
		TraverseLNR(root);
	}
	
	public static void insert(Node n, Node root)
	{
		{
			if(n.value < root.value && root.left == null)
			{
				root.left = n;
			}
			else if (n.value > root.value && root.right == null)
			{
				root.right = n;
			}
			else if(n.value < root.value && root.left != null)
			{
				root = root.left;
				insert(n, root);
			}
			else
			{
				root = root.right;
				insert(n, root);
						
			}
			
		}
	}
	
	
	public class Node
	{
		int value;
		Node left;
		Node right;
		
		public Node(int num)
		{
			value = num;
			left = null;
			right = null;
		}
	}
	
	public static void TraverseLNR(Node Root) {
		if(Root.left != null)
			TraverseLNR(Root.left);
		System.out.println(Root.value);
		if(Root.right != null)
			TraverseLNR(Root.right);
	}
	
	public void BubbleSort(int[] items, int size)
	{
		System.out.println("Begin Bubble Sort");
		int itemsSorted = 0;
		boolean flip;
		int b,t;
		do
		{
			flip = false; //begin a pass
			for (b = size - 1, t= size - 2; t >= itemsSorted; b--, t--)
				if(items[b] < items [t])
				{
					int temp;
					temp = items[b];
					items[b] = items[t];
					items[t] = temp;
					flip = true;
				}
			itemsSorted++;
			System.out.println("\nStep " + itemsSorted);
			for(int i = 0; i < size; i++)
			{
				System.out.println(items[i]);
			}
		} while (flip == true && itemsSorted != size - 1);	
	}
	
	public void HeapSort(int[] items, int size)
	{
		//Build the initial heap
		BuildHeap(items, size);
		//Swap the root node into its proper place
		for(int i = size; i > 0; i--)
		{
			int temp = items[i - 1];
			items[i - 1] = items[0];
			items[0] = temp;
			BuildHeap(items, i-1);
		}
		
		for(int i = 0; i < size; i++)
		{
			System.out.println(items[i]);
		}
	}
		
	public void BuildHeap(int[] items, int size)
	{
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		int highest = i;
		int left = 2 * i +1;
		int right = 2 * i +2;
		
		if(left < size && items[left] > items[highest] )
		{
			highest = left;
		}
		if (right < size && items[right] > items[highest] )
		{
			highest = right;
		}
		if(highest != i)
		{
			int temp = items[i];
			items[i] = items [highest];
			items[highest] = temp;
			BuildHeap(items, size);
		}
	}
	}
	
	public void MergeSort(int numArray[], int size)
	{
		int[] temp = new int[size];
		int leftIndex = 0;
		int rightIndex = size - 1;
		
		numArray = doMergeSort(numArray, temp, leftIndex, rightIndex);
		
		for(int i = 0; i < 10; i++)
		{
			System.out.println(numArray[i]);
		}
		
	}
	
	public int[] doMergeSort(int items[], int temp[], int leftIndex, int rightIndex)
	{
		int midIndex, nItems;
		nItems = rightIndex - leftIndex + 1;
		if(nItems == 1) //base case
			return null;
		midIndex = (rightIndex + leftIndex) / 2;
		doMergeSort(items, temp, leftIndex, midIndex); //first reduced problem
		doMergeSort(items, temp, midIndex + 1, rightIndex); //second reduced problem
		
		merge(items, temp, leftIndex, midIndex + 1, rightIndex); // general solution
		return items;
		
	}
	
	public void merge(int items[], int temp[], int leftIndex,
							 int midIndex, int rightIndex)
	{
		int leftEnd, nItems, tempsIndex;
		leftEnd = midIndex - 1;
		tempsIndex = leftIndex;
		nItems = rightIndex - leftIndex + 1;
		while ((leftIndex <= leftEnd) && (midIndex <= rightIndex)) //move items into temp
		{
			if(items[leftIndex] <= items[midIndex]) //from left sublist
			{
				temp[tempsIndex] = items[leftIndex];
				tempsIndex = tempsIndex + 1;
				leftIndex = leftIndex + 1;
			}
			else //move items from right sublist into temp
			{
				temp[tempsIndex] = items[midIndex];
				tempsIndex = tempsIndex + 1;
				midIndex = midIndex + 1;
			}
		} //end while
		if(leftIndex <= leftEnd) //left sublist (LS) is not empty
		{
			while(leftIndex <= leftEnd) //copy remainder of LS into temp
			{
				temp[tempsIndex] = items[leftIndex];
				leftIndex = leftIndex + 1;
				tempsIndex = tempsIndex +1;
			}
		} // end if
		else //right sublist (RS) is not empty
		{
			while (midIndex <= rightIndex) //copy remainder of RS into temp
			{
				temp[tempsIndex] = items[midIndex];
				midIndex = midIndex + 1;
				tempsIndex = tempsIndex + 1;
			}
		}
		for (int i = 0; i < nItems; i++) //copy array temp into array items
		{
			items[rightIndex] = temp[rightIndex];
			rightIndex = rightIndex - 1;
		}
		
	} //end merge method
	
	public void QuickSort(int[] items, int size)
	{
		int leftIndex = 0;
		int rightIndex = size - 1;
		items = doQuickSort(items, leftIndex, rightIndex);
		
		for(int i = 0; i < size; i++)
		{
		System.out.println(items[i]);
		}
	}
	
	public int[] doQuickSort(int[] items, int leftIndex, int rightIndex)
	{
		int i, j, temp, pivotValue, partitionSize;
		partitionSize = rightIndex - leftIndex + 1;
		if(partitionSize <= 1) //base case, one item to be sorted
			return null;
		pivotValue = items[(leftIndex + rightIndex) / 2];
		i = leftIndex; //initialize the two partition indices
		j = rightIndex; 
		//look for items in wrong partitions and switch them
		do
		{
			while (items[i] < pivotValue) //left item is in correct position
				i++;
			while (items[j] > pivotValue) //right item is in correct partition
				j--;
			if(i <= j) // the pointers have not crossed, switch items
			{
				temp = items[i]; 
				items[i] = items[j];
				items[j] = temp;
				i++;
				j--;
			}
		}  while (i <= j); //the pointers have not crossed
		//reduced problems
		doQuickSort(items, leftIndex, j); //sort the left partition
		doQuickSort(items, i, rightIndex); //sort the right partition
		return items;
	}
	
}

