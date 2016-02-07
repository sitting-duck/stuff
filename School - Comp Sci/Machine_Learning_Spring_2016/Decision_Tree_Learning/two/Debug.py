
class Debug(object):

    level = 2

    # level 0 prints out no debug statements

    # level 1 prints out the state of the training sets after each iteration and the values calculated for information gain

    # level 2 prints out all of the above and whether each iteration of the partitioning of the training set is homogenous

    #level 3 prints out all the separated partitions

    # level 4 prints out the entire calculations done for calculating entropy and information gain

    @staticmethod
    def log(*arguments):
        for argument in arguments:
            print " " + str(argument) + " ",
        print ""