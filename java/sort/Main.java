



public class Main {

	
	public static void main(String[] args)
	{
	
	int size = 10;
	int[] numArray = {50, 40, 63, 42, 55, 43, 70, 80, 35, 68};
	
	//BinaryTreeSort bTreeSort = new BinaryTreeSort(numArray, size);
	
	SortMethods mySorts = new SortMethods();
	
	//mySorts.BubbleSort(numArray, size);
	
	//mySorts.HeapSort(numArray, size);
	
	//mySorts.BinaryTreeSort(numArray, size);
	
	//mySorts.MergeSort(numArray, size);
	
	mySorts.QuickSort(numArray, size);
	
	}
}
