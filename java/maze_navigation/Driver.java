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
		DecisionTreeNode rootNode = new DecisionTreeNode(labrinth.start());
		DecisionTree decisionTree = new DecisionTree(rootNode, labrinth);

		labrinth.print();
		decisionTree.print();		

		driver.makeNextDecision(decisionTree.root(), decisionTree, labrinth);

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

	public boolean makeNextDecision(DecisionTreeNode lastDecision, DecisionTree tree, Labrinth labrinth) {

		System.out.println("makeNextDecision(): " + lastDecision.coordinate().toString());

		labrinth.print();
		tree.print();

		scan.nextLine();

		boolean atGoal = false;
		int choiceNumber = 0;
		int numberOfChoices = 8;
		while(atGoal == false && choiceNumber < numberOfChoices) {
			int thisDecisionChoice = lastDecision.nextChoice();
			Coordinate newCoordinate = labrinth.nextChoiceAsCoordinate(thisDecisionChoice, lastDecision.coordinate());
			DecisionTreeNode currentDecision = new DecisionTreeNode(newCoordinate);


			if(labrinth.isValid(thisDecisionChoice, lastDecision.coordinate())) {	
				// System.out.println("was valid: " + thisDecisionChoice);
				// record this decision choice
				System.out.println("before set: ");
				tree.print();

				labrinth.set(newCoordinate, "0");
				lastDecision.setChild(currentDecision);
				currentDecision.setParent(lastDecision);
				tree = tree.insertNode(currentDecision);

				System.out.println("after set: ");
				tree.print();
				
				if(labrinth.canEndPath(newCoordinate)) {
					labrinth.set(newCoordinate, "E");
					return true;
				} else {
					atGoal = makeNextDecision(currentDecision, tree, labrinth); // reduce problem
					if(atGoal == false) { // backtrack has occurred
						//un - record this decision choice
						System.out.println("BACKTRACK!!");
						lastDecision.setChild(null);
					}
				}
				//atGoal = makeNextDecision(currentDecision, tree, labrinth); // ??
			}
			choiceNumber += 1;
		}
		return atGoal;
	}

}