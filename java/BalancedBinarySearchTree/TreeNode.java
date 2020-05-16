

/**
* This class initializes the data members for the class TreeNode.
* It contains the class data members Data, Left, and Right.
* The class contains the constructor to initialize a new TreeNode
* 
* @version 1.0
*
*/
public class TreeNode {

	//A field for the integral data store in the node
	//changed to public
	public int Data;
	
	//a field for the link to the left subtree
	//changed to public
	public TreeNode Left;
	
	//a field for the link to the right subtree
	//changed to public
	public TreeNode Right;

	// a number for balancing the tree
	// the difference in the number of levels in the left and right sub-trees
	// numLevels(left) - numLevels(right) = balanceFactor
	public int balanceFactor;
	
	/**
	 * A constructor with no parameters that initializes the fields
	 * 
	 * @param no parameters needed
	 */
	public TreeNode()
	{
		Data = 0;
		Left = null;
		Right = null;
		balanceFactor = 0;
	}
	
}
