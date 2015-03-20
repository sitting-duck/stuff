__author__ = 'ashley tharp'


class Variable:
    """Variables in this class are integers.  Each variable has a domain of possible integers that it can be assigned.
    As the search proceeds, values are taken from the domain of possible ints for the variable until there is only 1
    left, or there are no possible valid assignments for this variable"""

    def __init__(self, varNameArg, domainArg = []):
        self.name = varNameArg
        self.domain = domainArg






