

/**
 * This class contains the data members and methods for the BalancedBinarySearchTree class.
 * It contains a constructor for the BalancedBinarySearchTree and initialized the TreeNode Root object. 
 * It contains methods to Insert an integer value, Fetch an integer value, Delete an integer value, 
 * Update an integer value, FindNode to find an integer value, and Traverse the tree. 
 * 
 * Version 1.0
 *
 */
public class BalancedBinarySearchTree {
	
	//a field storing the root node of the tree(a TreeNode object)
	TreeNode Root;
	
	/**
	 * A constructor with no parameters that initializes Root field as null
	 * 
	 * @param no parameters needed
	 */
	public BalancedBinarySearchTree() {
		Root = null;
	}
	
	/**
	 * Insert method that inserts a value (given by the parameter) into a new node into the tree.
	 * The method utilizes the TreeNodeWrapper to manage the TreeNode
	 * 
	 * @param newInt, an integer to be inserted into the tree
	 * 
	 * @return boolean true if insert successful
	 */
	public boolean Insert(int newInt) {
		//initialize the parent node
		TreeNodeWrapper p = new TreeNodeWrapper();
		//initialize the child node
		TreeNodeWrapper c = new TreeNodeWrapper();
		//initialize a new TreeNode
		TreeNode n = new TreeNode();
		//set value of TreeNode as integer passed in method
		n.Data = newInt;
		//initialize left node as null
		n.Left = null;
		//initialize right node as null
		n.Right = null;
		//will be inserted as a leaf so its balanceFactor will be zero
		n.balanceFactor = 0;
		//if tree is empty set a root node
		if(Root == null)
		{  
			Root = n;
		} else
		//determine which node is parent node using FindNode Method
		{  FindNode(newInt, p, c);
		//if new value is less than parent node then set as left node
		   if(newInt < p.Get().Data )
		   {  
			p.Get().Left = n;
		   }
		   else
		//else new value is more than parent node and set as right node
		   {  p.Get().Right = n; }
		}
		//insert successful 
		return true;
	}

	
	/**
	 * Fetch method that returns the value of of the node that matches integer passed to the method
	 * 
	 * @param num, int value to be fetched from the tree
	 * 
	 * @return int value from the node passed as parameter or value that is not in the tree
	 */
	public int Fetch(int num) {
		//initialize boolean field, set to true if value found in tree 
		boolean found;
		//initialize the parent node
		TreeNodeWrapper p = new TreeNodeWrapper();
		//initialize the child node
		TreeNodeWrapper c = new TreeNodeWrapper();
		//found set to true if FindNode methods locates value in the tree
		found = FindNode(num, p, c); //locate the node
		//if found is true print success message and return value of node
		if(found == true)
			{ System.out.println("The number you entered was found in the tree");
			return c.Get().Data; }
		else
		//if found is false print message that value not found and return integer not found
			{ System.out.println("\nThe number you entered is not in tree.");
			return num; }
	}
	
	
	//A method that deletes a value (given by the parameter) from the AVL tree
	/**
	 * Delete method deletes the value given as a parameter from the tree 
	 * method re-established parent and child nodes accordingly when node is deleted
	 * 
	 * @param num, integer value to be deleted from the tree
	 * 
	 * @return boolean true if successful and false if not
	 */
	public boolean Delete(int num) {
		//initialize boolean field, set to true if value found in tree
		boolean found;
		//initialize the parent node using the TreeNodeWrapper
		TreeNodeWrapper p = new TreeNodeWrapper();
		//initialize the child node using the TreeNodeWrapper
		TreeNodeWrapper c = new TreeNodeWrapper();
		//initialize largest field to re-allocate parent/child nodes
		TreeNode largest;
		//initialize nextLargest field to re-allocate parent/child nodes
		TreeNode nextLargest;
		//found set to true if FindNode methods locates value in the tree
		found = FindNode(num, p, c);
		//if node not found return false
		if(found == false)
			return false;
		else //identify the case number
		{
			//case 1: deleted node has no children
			//if left and right child nodes of value are both null node has no children
			if(c.Get().Left == null && c.Get().Right == null)
				//if parent left node is equal to child node then deleted node is a left child
				if(p.Get().Left == c.Get())
					p.Get().Left = null;
				else  //deleted node is a right child
					p.Get().Right = null;
			//case 2: deleted node has 1 child
			//if deleted node only has 1 child node
			else if(c.Get().Left == null || c.Get().Right == null)
			{
				//if parent left node is equal to child node then deleted node is a left child
				if(p.Get().Left == c.Get())
				{
					//if deleted node is a left child then set deleted node child node as child to parent node
					if(c.Get().Left != null) //deleted node has a left child
						p.Get().Left = c.Get().Left;
					else
						p.Get().Left = c.Get().Right;
				}
				else //if deleted node is a right child then set deleted node child node as child to parent node
				{
					if(c.Get().Left != null) //deleted node has a left child
						p.Get().Right = c.Get().Left;
					else
						p.Get().Right = c.Get().Right;
				}
			}
			//case 3: deleted node has two children
			else
			{
				//set the nextLargest as the left child of deleted node
				nextLargest = c.Get().Left;
				//set the largest as the right node of the nextLargest node
				largest = nextLargest.Right;
				//if right node is not null then left child has a right subtree
				if(largest != null) 
				{
					//while loop to move down the right subtree and re-allocate after node is deleted
					while(largest.Right != null) //move down right subtree
					{
						nextLargest = largest;
						largest = largest.Right;
					}
					//overwrite the deleted node
					c.Get().Data = largest.Data; 
					// save the left subtree
					nextLargest.Right = largest.Left; 
				}
				else //left child does not have a right subtree
				{
					//save the right subtree
					nextLargest.Right = c.Get().Right; 
					//deleted node is a left child
					if(p.Get().Left == c.Get()) 
						//jump around deleted node
						p.Get().Left = nextLargest; 
					else  //deleted node is a right child
						p.Get().Right = nextLargest; //jump around deleted node
				}
			}
			//return true is delete is successful
			return true;
		}
	}
	
	//A method that updates a value (given by the first parameter) from the AVL tree 
	//to a new value (given by the second parameter)
	/**
	 * Update method updates a value given by the first parameter from the tree
	 * to a new value given by the second parameter
	 * 
	 * @param oldNum, integer value to be deleted from the tree
	 * @param newNum, integer value to be added in place of the deleted value
	 * 
	 * @return true if successful and false if not
	 */
	public boolean Update(int oldNum, int newNum) {
		//attempt to delete node and return false if unsuccessful
		if(Delete(oldNum) == false)
			return false;
		//attempt to insert new node and return false if unsuccessful
		else if(Insert(newNum) == false)
			return false;
		//return true if update successful
		return true;
	}
	
	/**
	 * FindNode method that finds a value in the tree given as a parameter
	 * 
	 * @param num, integer value to find in the tree
	 * 
	 * @param parent, TreeNodeWrapper object of parent node
	 * @param child, TreeNodeWrapper object of child node
	 * 
	 * @return boolean true if successful and false if unsuccessful
	 */
	private boolean FindNode(int num, TreeNodeWrapper parent, TreeNodeWrapper child) {
		//set parent node of TreeNodeWrapper as Root
		parent.Set(Root);
		//set child node as TreeNode Wrapper as Root
		child.Set(Root);
		//if root is null, tree is empty
		if(Root == null) //tree is empty
			return true;
		//while loop which searches tree until empty child node is found
		while(child.Get() != null)
		{  if(child.Get().Data == num) // node found
			return true;
			//if node not found use TreeNodeWrapper search remaining nodes
		   else {
			parent.Set(child.Get());
			if(num < child.Get().Data)
				child.Set(child.Get().Left);
			else
				child.Set(child.Get().Right);
		   }	
		}
		//return false if node not found
		return false;
	}

	 
	
	
	/**
	 * TraverseLNR method traverses tree from left subtree, root, then right subtree
	 * and outputs the values
	 * 
	 * @param Root, TreeNode object of Root Node
	 */
	public void TraverseLNR(TreeNode Root) {
		if(Root.Left != null)
			TraverseLNR(Root.Left);
		System.out.println(Root.Data);
		if(Root.Right != null)
			TraverseLNR(Root.Right);
	}
	
	/**
	 * TraverseLRN method traverses tree from left subtree, right subtree, then root
	 * and outputs the values
	 * 
	 * @param Root, TreeNode object of Root Node
	 */
	public void TraverseLRN(TreeNode Root) {
		if(Root.Left != null)
			TraverseLNR(Root.Left);
		if(Root.Right != null)
			TraverseLNR(Root.Right);
		System.out.println(Root.Data);
		
	}
	
	/**
	 * TraverseNLR method traverses tree from root, left subtree, then right subtree
	 * and outputs the values
	 * 
	 * @param Root, TreeNode object of Root Node
	 */
	public void TraverseNLR(TreeNode Root) {
		System.out.println(Root.Data);
		if(Root.Left != null)
			TraverseLNR(Root.Left);
		if(Root.Right != null)
			TraverseLNR(Root.Right);
	}
	
	/**
	 * TraverseNRL method traverses tree from root, right subtree, then left subtree
	 * and outputs the values
	 * 
	 * @param Root, TreeNode object of Root Node
	 */
	public void TraverseNRL(TreeNode Root) {
		System.out.println(Root.Data);
		if(Root.Right != null)
			TraverseLNR(Root.Right);
		if(Root.Left != null)
			TraverseLNR(Root.Left);
	}
	
	/**
	 * TraverseRLN method traverses tree from right subtree, left subtree, then root
	 * and outputs the values
	 * 
	 * @param Root, TreeNode object of Root Node
	 */
	public void TraverseRLN(TreeNode Root) {
		if(Root.Right != null)
			TraverseLNR(Root.Right);
		if(Root.Left != null)
			TraverseLNR(Root.Left);
		System.out.println(Root.Data);
	}
	
	/**
	 * TraverseRNL method traverses tree from right subtree, root, then left subtree
	 * and outputs the values
	 * 
	 * @param Root, TreeNode object of Root Node
	 */
	public void TraverseRNL(TreeNode Root) {
		if(Root.Right != null)
			TraverseLNR(Root.Right);
		System.out.println(Root.Data);
		if(Root.Left != null)
			TraverseLNR(Root.Left);
	}
}
