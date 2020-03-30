import java.util.Random;

public class DecisionTreeNode {
	
	private Coordinate coordinate;

	private DecisionTreeNode parent = null;

	private DecisionTreeNode child = null;

	private Random random_number_generator;

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
		return random_number_generator.nextInt(4);
	}

	public Coordinate coordinate() {
		return coordinate;
	}

	public void setChild(DecisionTreeNode _node) {
		child = _node;
	}

	public void setParent(DecisionTreeNode _node) {
		parent = _node;
	}
}
