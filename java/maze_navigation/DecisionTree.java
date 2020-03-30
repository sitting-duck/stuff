import java.util.Scanner;


public class DecisionTree {

	private Labrinth labrinth;

	private DecisionTreeNode root;

	private Scanner scan;

	public DecisionTree(DecisionTreeNode _root, Labrinth _labrinth) {
		labrinth = _labrinth;
		root = _root;
		scan = new Scanner(System.in);
	}

	

	public DecisionTree insertNode(DecisionTreeNode _node) {
		System.out.println("insertNode: " + _node.toString());
		DecisionTreeNode currentNode = root;
		boolean isNull = currentNode.child() == null;

		int num = 0;
		while(!isNull) {
			isNull = currentNode.child() == null;
			//System.out.println("isNull: " + isNull);
			currentNode = currentNode.child();
			num++;
			if(num == 15) {
				break;
			}
		}
		if(currentNode != null) {
			currentNode.setChild(_node);	
		}

		return this;

	}

	public DecisionTreeNode root() {
		return root;
	}

	public void print() {
		System.out.println("tree");
		
		DecisionTreeNode currentNode = root;
		System.out.println("root: " + currentNode.toString());
		boolean isNull = currentNode.child() == null;

		if(!isNull) {
			currentNode = currentNode.child();
		}
		

		int num = 0;
		while(!isNull) {
			isNull = currentNode.child() == null;
		// System.out.println("isNull: " + isNull);
			System.out.println("\t" + currentNode.toString());
			currentNode = currentNode.child();
			num++;
			if(num == 15) {
				break;
			}
		}
	}
}
