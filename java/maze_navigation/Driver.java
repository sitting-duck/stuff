import java.util.Scanner;

public class Driver {

	private Scanner scan;

	public Driver() {
		scan = new Scanner(System.in);
	}

	public static void main(String[] args) {

		// create decision tree

		Driver driver = new Driver();
		Labrinth labrinth = new Labrinth();
		Coordinate start = labrinth.start();
		DecisionTreeNode rootNode = new DecisionTreeNode(labrinth.start(), labrinth);
		DecisionTree tree = new DecisionTree(rootNode);

		
		driver.makeNextDecision(tree.root(), tree);

		tree.print();

		labrinth = new Labrinth(tree);
		//System.out.println("labrinth: ");
		//labrinth.print();
		
		// fill in randomly some spots with empty until we hit minEmpty
		//System.out.println("Random!!");
		while(labrinth.numEmpty() < labrinth.minEmpty()) {
			Coordinate random = labrinth.random();
			System.out.println("\t" + random.toString());
			boolean isWall = labrinth.isWall(random);
			if(isWall) {
				labrinth.set(random, "0");
			}
		}

		//labrinth.print();
		DecisionTreeNode roboRoot = new DecisionTreeNode(start, labrinth);
		System.out.println("roboRoot: " + roboRoot.coordinate().toString());
		DecisionTree roboTree = new DecisionTree(roboRoot);

		driver.robotWalk(roboTree.root(), labrinth, roboTree);

		System.out.println("labrinth!");
		labrinth.print();

		System.out.println("roboTree!");
		roboTree.printLabrinth();

	}

	public boolean robotWalk(DecisionTreeNode lastDecision, Labrinth labrinth, DecisionTree roboTree) {

		System.out.println("robotWalk(): " + lastDecision.coordinate().toString());

		// DecisionTreeNode leaf = pathTree.getLeaf();
		
		System.out.println("roboTree");		
		roboTree.print();
		labrinth.print();
		roboTree.printRoboWalk(labrinth);

		// System.out.println("roboTree");
		// roboTree.printLabrinth();
		// roboTree.print();

		scan.nextLine();

		boolean atGoal = false;
		int choiceNumber = 0;
		int numberOfChoices = 4;
		while(atGoal == false && choiceNumber < numberOfChoices) {
			System.out.println("choiceNumber: " + choiceNumber + " atGoal: " + atGoal + " lastDecision: " + lastDecision.coordinate().toString());
			int thisDecisionChoice = lastDecision.nextChoice();
			System.out.println("thisDecisionChoice: " + thisDecisionChoice);
			Coordinate newCoordinate = labrinth.nextChoiceAsCoordinate(thisDecisionChoice, lastDecision.coordinate());
			DecisionTreeNode currentDecision = new DecisionTreeNode(newCoordinate, labrinth);

			boolean canWalk = labrinth.canWalk(thisDecisionChoice, lastDecision.coordinate());
			System.out.println("canWalk: " + canWalk);
			if(canWalk) {	
				// System.out.println("was valid: " + thisDecisionChoice);
				// record this decision choice
				// System.out.println("before set: ");
				// tree.print();

				if(labrinth.at(newCoordinate) != "E") {
					labrinth.set(newCoordinate, "*");	
				}
				
				lastDecision.setChild(currentDecision);
				currentDecision.setParent(lastDecision);
				roboTree = roboTree.insertNode(currentDecision);

				// System.out.println("after set: ");
				// tree.print();
				
				if(labrinth.at(newCoordinate) == "E") {
					System.out.println("found the end!!");
					return true;
				} else {

					atGoal = robotWalk(currentDecision, labrinth, roboTree); // reduce problem
					// System.out.println("atGoal " + atGoal);
					if(atGoal == false) { // backtrack has occurred
						//un - record this decision choice
						System.out.println("BACKTRACK!!");
						//System.out.println("lastDecision.coordinate: " + lastDecision.coordinate());
						// if(labrinth.at(lastDecision.coordinate()) == "0") {
						// 	labrinth.set(lastDecision.coordinate(), "1");
						// }
						
						lastDecision.setChild(null);
						roboTree = roboTree.removeLeaf();
					}
				}
			}
			choiceNumber += 1;
		}
		// System.out.println("exit while loop");
		return atGoal;
	}

	public boolean makeNextDecision(DecisionTreeNode lastDecision, DecisionTree tree) {

		System.out.println("makeNextDecision(): " + lastDecision.coordinate().toString());

		DecisionTreeNode leaf = tree.getLeaf();
		tree.printLabrinth();

		// scan.nextLine();

		boolean atGoal = false;
		int choiceNumber = 0;
		int numberOfChoices = 4;
		while(atGoal == false && choiceNumber < numberOfChoices) {
			System.out.println("choiceNumber: " + choiceNumber + " atGoal: " + atGoal + " lastDecision: " + lastDecision.coordinate().toString());
			int thisDecisionChoice = lastDecision.nextChoice();
			System.out.println("thisDecisionChoice: " + thisDecisionChoice);
			Coordinate newCoordinate = leaf.labrinth().nextChoiceAsCoordinate(thisDecisionChoice, lastDecision.coordinate());
			DecisionTreeNode currentDecision = new DecisionTreeNode(newCoordinate, leaf.labrinth());

			boolean isValid = leaf.labrinth().isValid(thisDecisionChoice, lastDecision.coordinate());
			System.out.println("isValid: " + isValid);
			if(isValid) {	
				// System.out.println("was valid: " + thisDecisionChoice);
				// record this decision choice
				// System.out.println("before set: ");
				// tree.print();

				leaf.labrinth().set(newCoordinate, "0");
				lastDecision.setChild(currentDecision);
				currentDecision.setParent(lastDecision);
				tree = tree.insertNode(currentDecision);

				// System.out.println("after set: ");
				// tree.print();
				
				if(leaf.labrinth().canEndPath(newCoordinate)) {
					leaf.labrinth().set(newCoordinate, "E");
					return true;
				} else {

					atGoal = makeNextDecision(currentDecision, tree); // reduce problem
					// System.out.println("atGoal " + atGoal);
					if(atGoal == false) { // backtrack has occurred
						//un - record this decision choice
						System.out.println("BACKTRACK!!");
						if(leaf.labrinth().at(lastDecision.coordinate()) == "0") {
							leaf.labrinth().set(lastDecision.coordinate(), "1");
						}
						
						lastDecision.setChild(null);
						tree = tree.removeLeaf();
					}
				}
			}
			choiceNumber += 1;
		}
		// System.out.println("exit while loop");
		return atGoal;
	}

}