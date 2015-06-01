__author__ = 'ashley'

import operator

class Constraint:

    """The constraint class contains 2 variables and an operator =, !, <, or > to indicate the relationship of the two variables.
    These are what would be referred to as binary constraints"""

    def __init__(self, var1Arg, operatorArg, var2Arg):
        self.var1 = var1Arg
        self.operator = operatorArg
        self.var2 = var2Arg

        self.ops = {">": operator.gt, "<": operator.lt, "=": operator.eq, "!": operator.ne}
