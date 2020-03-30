import java.util.Random;
import java.util.Scanner;

public class DecisionTreeNode {
	
	private Coordinate coordinate;

	private DecisionTreeNode parent = null;

	private DecisionTreeNode child = null;

	private Random random_number_generator;

	private int[] choicesTried = {0, 0, 0, 0};

	public DecisionTreeNode(Coordinate _coordinate) {
		coordinate = _coordinate;
		random_number_generator = new Random();
	}

	public DecisionTreeNode(Coordinate _coordinate, DecisionTreeNode _parent) {
		coordinate = _coordinate;
		parent = _parent;
		random_number_generator = new Random();
	}

	public int decisionNumber() { // returns the level of the tree
		int num = 0;
		while(parent != null) {
			num++;
		}
		return num;
	}

	public int nextChoice() {
		int rand; 
		while(true) { // loop until we get a choice we haven't tried before
			rand = random_number_generator.nextInt(4);
			if(choicesTried[rand] == 0) { // we have not tried this choice before 
				choicesTried[rand] = 1;
				return rand;
			} 
		}
	}

	public Coordinate coordinate() {
		return coordinate;
	}

	public String toString() {
		return coordinate.toString();
	}

	public DecisionTreeNode child() {
		return child;
	}

	public void setChild(DecisionTreeNode _node) {
		if(_node != null) {
			_node.parent = child;	
		}
		
		child = _node;

	}

	public void setParent(DecisionTreeNode _node) {
		parent = _node;
	}
}
