

public class TreeNodeWrapper {
	
	//A reference to a tree node initialized as null
	TreeNode TreeNodeRef = null;
	
	/**
	 * A constructor for TreeNodeWrapper with no parameters
	 * 
	 * @param no parameters needed
	 */
	public TreeNodeWrapper() {
	}
	
	/**
	 * Get() method returns the TreeNode of the wrapper
	 * 
	 * @param no parameters needed
	 *  
	 * @return TreeNodeRef object
	 */
	public TreeNode Get() {
		return TreeNodeRef;
	}
	
	/**
	 * Set() method adds a TreeNode to the wrapper
	 * 
	 * @param t TreeNodeRef object of the TreeNode
	 */
	public void Set(TreeNode t) {
		TreeNodeRef = t;
	}

	/**
	 * Height() method returns the "height" of the tree. 
	 * Height is the number of nodes along the longest path
	 * from the root node down to the furthese leaf node 
	 * 
	 * @param The node we will compute the height from
	 * 
	 * @return int height
	 */
	public int height() {
		return height(TreeNodeRef);
	}

	/**
	* Private recursive call - iterates down left and right children,
	* returning the height of the tallest sub tree
	*/
	private int height(TreeNode t)
	{
		// base case tree is empty
		if(t == null) {
			return 0;
		}

		// if tree is not empty then height = 1 + max of left and right heights
		return 1 + Math.max(height(t.Left), height(t.Right));
	}

	/**
	 * IsBalanced method that returns true if binary tree with node as root is 
	 * height balanced
	 * 
	 * @param Root, TreeNode object of Root Node
	 *
	 * @return boolean true if height balanced and false if not height balanced
	 */
	 public boolean isBalanced(TreeNode t)
	 {
		// height of the left subtree
		int leftHeight; 

		// height of the right subtree
		int rightHeight;

		// if tree is empty then return true
		if(t == null) {
			return true;
		}

		leftHeight = height(t.Left);
		rightHeight = height(t.Right);

		if(Math.abs(leftHeight - rightHeight) <= 1 && 
					isBalanced(t.Left) &&
					isBalanced(t.Right)) {
			return true;
		}
		
		// if we reach here then the tree is not height balanced
		return false;
	 }
	

}
