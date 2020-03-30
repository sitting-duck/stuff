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
		DecisionTreeNode rootNode = new DecisionTreeNode(labrinth.start(), labrinth);
		DecisionTree decisionTree = new DecisionTree(rootNode);

		labrinth.print();
		decisionTree.print();		

		driver.makeNextDecision(decisionTree.root(), decisionTree);

		labrinth.print();
		decisionTree.print();

		//Testing insert node
		// DecisionTreeNode child1 = new DecisionTreeNode(new Coordinate(0, 0));
		// decisionTree.insertNode(child1);

		// DecisionTreeNode child2 = new DecisionTreeNode(new Coordinate(0, 1));
		// decisionTree.insertNode(child2);

		// DecisionTreeNode child3 = new DecisionTreeNode(new Coordinate(0, 2));
		// decisionTree.insertNode(child3);

		// DecisionTreeNode child4 = new DecisionTreeNode(new Coordinate(0, 3));
		// decisionTree.insertNode(child4);

		// DecisionTreeNode child5 = new DecisionTreeNode(new Coordinate(0, 4));
		// decisionTree.insertNode(child5);

		// DecisionTreeNode child6 = new DecisionTreeNode(new Coordinate(0, 5));
		// decisionTree.insertNode(child6);

		// DecisionTreeNode child7 = new DecisionTreeNode(new Coordinate(0, 6));
		// decisionTree.insertNode(child7);

		// DecisionTreeNode child8 = new DecisionTreeNode(new Coordinate(0, 7));
		// decisionTree.insertNode(child8);

		// decisionTree.print();

	}

	public boolean makeNextDecision(DecisionTreeNode lastDecision, DecisionTree tree) {

		System.out.println("makeNextDecision(): " + lastDecision.coordinate().toString());

		DecisionTreeNode leaf = tree.getLeaf();
		System.out.println("leaf labrinth: " + leaf.labrinth());

		leaf.labrinth().print();
		tree.print();

		scan.nextLine();

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
				System.out.println("before set: ");
				tree.print();

				leaf.labrinth().set(newCoordinate, "0");
				lastDecision.setChild(currentDecision);
				currentDecision.setParent(lastDecision);
				tree = tree.insertNode(currentDecision);

				System.out.println("after set: ");
				tree.print();
				
				if(leaf.labrinth().canEndPath(newCoordinate)) {
					leaf.labrinth().set(newCoordinate, "E");
					return true;
				} else {

					atGoal = makeNextDecision(currentDecision, tree); // reduce problem
					System.out.println("atGoal " + atGoal);
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
				//atGoal = makeNextDecision(currentDecision, tree, labrinth); // ??
			}
			choiceNumber += 1;
		}
		System.out.println("exit while loop");
		return atGoal;
	}

}