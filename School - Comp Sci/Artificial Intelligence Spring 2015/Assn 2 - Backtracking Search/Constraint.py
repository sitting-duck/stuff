__author__ = 'ashley'

import operator

class Constraint:

    """The constraint class contains 2 variables and an operator =, !, <, or > to indicate the relationship of the two variables.
    These are what would be referred to as binary constraints"""

    def __init__(self, var1Arg, operatorArg, var2Arg):

	    # the first variable in the constraint
        self.var1 = var1Arg

	    # the constraint operator. Can be =, !, <, or > to indicate the relationship of the two variables.
        self.operator = operatorArg

	    # the second variable in the constraint
        self.var2 = var2Arg

		# container for the set of valid operator characters
        self.ops = {">": operator.gt, "<": operator.lt, "=": operator.eq, "!": operator.ne}
