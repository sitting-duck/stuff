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

	// public Coordinate nextChoiceAsCoordinate() {
	// 	//     // pick a random unvisited neighbor

	// 	//     // whichWay is a number such that:
	// 	//     // 0 = NORTH
	// 	//     // 1 = EAST
	// 	//     // 2 = SOUTH
	// 	//     // 3 = WEST
 //    	int whichWay = -1;
 //    	while(true) {
 //    		whichWay = random_number_generator.nextInt(4);

	// 		if(whichWay == 0) {        // NORTH
	// 			return getNorth();
	// 		} else if(whichWay == 1) { // EAST
	// 				return getEast();
	// 		} else if(whichWay == 2) { // SOUTH
	// 			return getSouth();
	// 		} else { 				   // WEST
	// 			return getWest();
	// 		}
 //    	}
	// }

	

	// public Coordinate nextChoiceSafe() {
	// 	//     // pick a random unvisited neighbor

	// 	//     // whichWay is a number such that:
	// 	//     // 0 = NORTH
	// 	//     // 1 = EAST
	// 	//     // 2 = SOUTH
	// 	//     // 3 = WEST
 //    	int whichWay = -1;
 //    	while(true) {
 //    		whichWay = random_number_generator.nextInt(4);

	// 		if(whichWay == 0) {        // NORTH

	// 			if(canBreakNorth()) {
	// 				return getNorth();
	// 			}
				
	// 		} else if(whichWay == 1) { // EAST

	// 			if(canBreakEast()) {
	// 				return getEast();
	// 			}

	// 		} else if(whichWay == 2) { // SOUTH

	// 			if(canBreakSouth()) {
	// 				return getSouth();
	// 			}			

	// 		} else { 				   // WEST

	// 			if(canBreakWest()) {
	// 				return getWest();
	// 			}			

	// 		}	
 //    	}
		
	// }

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
