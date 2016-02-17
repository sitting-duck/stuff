from Classify import Classify
from utils.ParseTools import ParseTools
from utils.PrintTools import PrintTools
from Training import Training


def main():

    problem = Training()




    accuracy_training_for_each_sample_size = []
    accuracy_testing_for_each_sample_size = []

    for i in range(0, 10):
        num_examples = i * 1

        training_set = ParseTools.get_training_set(None, num_examples + 2)
        testing_set = ParseTools.get_testing_set(None)

        problem.create_decision_tree(training_set)

        accuracy_training_set = Classify.get_accuracy(problem.decision_tree, training_set)
        accuracy_testing_set = Classify.get_accuracy(problem.decision_tree, testing_set)

        accuracy_training_for_each_sample_size.append(accuracy_training_set)
        accuracy_testing_for_each_sample_size.append(accuracy_testing_set)

    training_set_accuracy_file = open("./results/training_set_accuracy.txt", "w")
    print "training set accuracy"
    for j in range(0, len(accuracy_training_for_each_sample_size)):
        print "num examples: " + str(j) + " acc: " + str(accuracy_training_for_each_sample_size[j])
        training_set_accuracy_file.write(str(accuracy_training_for_each_sample_size[j]) + '\n')
    training_set_accuracy_file.close()

    print "\n\n"

    testing_set_accuracy_file = open("./results/testing_set_accuracy.txt", "w")
    print "testing set accuracy"
    for j in range(0, len(accuracy_testing_for_each_sample_size)):
        print "num examples: " + str(j) + " acc: " + str(accuracy_testing_for_each_sample_size[j])
        testing_set_accuracy_file.write(str(accuracy_testing_for_each_sample_size[j]) + '\n')
    testing_set_accuracy_file.close()

    # print "\n\n\nacc train set: " + str(accuracy_training_set)
    # print "acc test set: " + str(accuracy_testing_set) + "\n\n\n"

    #print "\n\nfinal tree: \n\n"
    #PrintTools.print_in_order(problem.decision_tree, problem.training_data, problem.decision_tree.root)

if __name__ == '__main__':
    main()
