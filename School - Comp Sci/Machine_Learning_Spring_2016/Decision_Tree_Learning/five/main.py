from utils.ParseTools import ParseTools
from utils.PrintTools import PrintTools
from Problem import Problem


def main():

    problem = Problem()

    training_set = ParseTools.get_training_set()

    problem.create_decision_tree(training_set)

    print "\n\nfinal tree: \n\n"
    PrintTools.print_in_order(problem.decision_tree, problem.training_data, problem.decision_tree.root)

if __name__ == '__main__':
    main()
