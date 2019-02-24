
class Problem:

    firstShore = 'wsc'
    secondShore = ''

    def __init__(self):
        pass

    @staticmethod
    def solve(firstShore, secondShore):

        currentShore = firstShore
        otherShore = secondShore

        while(Problem.isComplete(firstShore, secondShore) is False):
            Problem.printState(firstShore, secondShore)

            nextChar = Problem.pickNextMove(currentShore)

            newProblemState = Problem.move(nextChar, currentShore, otherShore)

            #update the state
            currentShore = newProblemState[0]
            otherShore = newProblemState[1]

            #swap shores
            temp = currentShore
            currentShore = otherShore
            otherShore = temp

    @staticmethod
    def move(char, source, destination):
        """
        moves the specified character from the source to the destination

        :param char: which character
        :param source: which shore we are taking the character from
        :param destination: which shore we are moving the characrer to
        :return: a tuple containg the state of the first and second shore in that order
        """

        newSource = Problem.takeCharFromShore(char, source)

        newDestination = Problem.addCharToShore(char, destination)

        return newSource, newDestination

    @staticmethod
    def printState(firstShore, secondShore):
        """
        prints the current state of the problem to the console
        :return: none
        """

        print firstShore + "        " + secondShore

    @staticmethod
    def pickNextMove(currentShore):
        """
        determine the next safe move

        :param currentShore: the state of the current shore
        :return: a character representing which character is to be moved
        """

        for i in range(0, len(currentShore)):
            currentChar = currentShore[i]
            if Problem.isSafe(Problem.takeCharFromShore(currentChar, currentShore)):
                return currentChar

    @staticmethod
    def takeCharFromShore(char, shore):
        """
        returns the string representing the state of the shore after the character has been moved

        :param char: character to remove from shore
        :param shore: the state of the current shore
        :return: the state of the shore after the character has been removed
        """

        assert char in shore, 'no char %s on shore' % char

        return shore.replace(char, '')

    @staticmethod
    def addCharToShore(char, shore):
        """

        :param char: which char we are adding
        :param shore: the current state of the shore we are adding it to
        :return: the string representing the new state of the shore after we have added the characer
        """

        assert char not in shore, 'error char %s already on shore' % char
        shore += char

        return shore

    @staticmethod
    def isComplete(firstShore, secondShore):
        """
        indicates whether the problem has been soved yet

        :param firstShore: state of the first shore
        :param secondShore: state of the second shore
        :return: BOolean indicating whether the problem is solved
        """
        if Problem.isSafe(firstShore) and Problem.isSafe(secondShore):
            return True
        else:
            return False

    @staticmethod
    def bothSafe(firstShore, secondShore):
        pass

    @staticmethod
    def isSafe(shore_state):
        """
        Tells whether it is safe to leave this shore in the current state

        :param shore_state: a string representing which characters are on the shore in question
        :return: a boolean indicating whether it is safe to leave this shore
        """

        if ('w' in shore_state and 's' in shore_state) or \
            's' in shore_state and 'c' in shore_state:
                return False
        else:
            return True


