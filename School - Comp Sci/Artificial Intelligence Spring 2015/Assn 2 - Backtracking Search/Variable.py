__author__ = 'ashley tharp'


class Variable:
    """Variables in this class are integers.  Each variable has a domain of possible integers that it can be assigned.
    As the search proceeds, values are taken from the domain of possible ints for the variable until there is only 1
    left, or there are no possible valid assignments for this variable"""

    def __init__(self, varNameArg, domainArg = [], degreeArg = 0):

	    # name of the variable
        self.name = varNameArg

        # the set of possible values that can be assigned to this variable.  (Note: there may be values in the domain that violate constraints, it the point of this
	    # program to eliminate all values that violate constraints from the domain of every variable)
        self.domain = domainArg

        self.degree = degreeArg

    def degree(self):
        return self.degree





