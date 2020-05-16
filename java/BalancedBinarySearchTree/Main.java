
public class Main {

	/**
	 * The main program; no parameters needed
	 * 	  
	 * @param args An array of strings that contains the command line argument.
	 */
	public static void main(String[] args) {
		
		//Create new BalancedBinarySearchTree object
		BalancedBinarySearchTree bTree = new BalancedBinarySearchTree();
		
		//Insert 10 integer values into the tree
		bTree.Insert(5);
		bTree.Insert(3);
		bTree.Insert(2);
		bTree.Insert(1);
		bTree.Insert(4);
		bTree.Insert(7);
		bTree.Insert(6);
		bTree.Insert(9);
		bTree.Insert(8);
		bTree.Insert(10);
		
		//traverse the tree from left, node, right
		bTree.TraverseLNR(bTree.Root);
		System.out.println("\n");
		
		//traverse the tree from left, right, node
		bTree.TraverseLRN(bTree.Root);
		System.out.println("\n");
		
		//traverse the tree from node, left, right
		bTree.TraverseNLR(bTree.Root);
		System.out.println("\n");
		
		//traverse the tree from node, right, left
		bTree.TraverseNRL(bTree.Root);
		System.out.println("\n");
		
		//traverse the tree from right, left, node
		bTree.TraverseRLN(bTree.Root);
		System.out.println("\n");
		
		//traverse the tree from left, node, right
		bTree.TraverseRNL(bTree.Root);
		System.out.println("\n");
		
		//fetch number that is in tree
		System.out.println(bTree.Fetch(7));
		System.out.println("\n");
		
		//fetch number that is not in tree
		System.out.println(bTree.Fetch(22));
		System.out.println("\n");
		
		//demonstrate update method by replace 7 with 15
		bTree.Update(7, 15);
		
		bTree.TraverseLNR(bTree.Root);
		System.out.println("\n");
		
		//attempt to delete node not in tree
		System.out.println(bTree.Delete(7));
		System.out.println("\n");
		
		bTree.TraverseLNR(bTree.Root);
		System.out.println("\n");
		
		//delete node found in tree
		System.out.println(bTree.Delete(15));
		System.out.println("\n");
		
		//traverse the tree from left, node, right
		bTree.TraverseLNR(bTree.Root);
		
	}
}
		

