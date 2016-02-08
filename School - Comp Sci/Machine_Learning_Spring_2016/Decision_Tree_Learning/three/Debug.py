
class Debug(object):

    level = 4

    # level 0 prints out no debug statements

    # level 1 prints out the state of the training sets after each iteration and the values calculated for information gain

    # level 3 prints out all the separated partitions

    # level 4 prints out the entire calculations done for calculating entropy and information gain

    # level 5 prints out all of the above and whether each iteration of the partitioning of the training set is homogenous

    @staticmethod
    def log(*arguments):
        for argument in arguments:
            print " " + str(argument) + " ",
        print ""