
from Print_Tools import  Print_Tools
from Problem import Problem
from Tests import Tests
from Tests_PlayTennis import Tests_PlayTennis

def main():

    #todo: add len checks in all the functions where a row or column is fetched from the training set\
    # this is important because the training set will change in size as it is passed through the tree

    problem = Problem()

    training_set = problem.training_data.get_training_set()

    problem.create_decision_tree(training_set)

    print "\n\nfinal tree: \n\n"
    Print_Tools.print_in_order(problem.decision_tree, problem.training_data, problem.decision_tree.root)

if __name__ == '__main__':
    main()