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

	public boolean makeNextDecision(DecisionTreeNode lastDecision) {



		System.out.println("makeNextDecision(): " + lastDecision.coordinate().toString());

		labrinth.print();
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
				labrinth.set(newCoordinate, "0");
				lastDecision.setChild(currentDecision);
				currentDecision.setParent(lastDecision);
				
				if(labrinth.canEndPath(newCoordinate)) {
					labrinth.set(newCoordinate, "E");
					return true;
				} else {
					//atGoal = makeNextDecision(currentDecision); // reduce problem
					if(atGoal == false) { // backtrack has occurred
						//un - record this decision choice
						lastDecision.setChild(null);
					}
				}
				atGoal = makeNextDecision(currentDecision); // ??
			}
			choiceNumber += 1;
		}
		return atGoal;
	}

	public DecisionTreeNode root() {
		return root;
	}

	public static void main(String[] args) {

		// create decision tree

		Labrinth labrinth = new Labrinth();
		DecisionTree decisionTree = new DecisionTree(new DecisionTreeNode(labrinth.start()), labrinth);

		decisionTree.makeNextDecision(decisionTree.root());

		labrinth.print();

	}

}