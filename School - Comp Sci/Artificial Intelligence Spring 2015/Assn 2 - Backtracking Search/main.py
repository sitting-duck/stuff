__author__ = 'ashley'

# This file will contain what would normally be the main function and other classless functions in a C++ program

import argparse
import init
from Node import Node
from CSP import CSP
from Backtracking_Search import Backtracking_Search

# variables: each variable has a name and a domain.  The domain is a set of possible values for the variable.
variables = []

# constraints: constraints are applied to variable assignments.  If a variable assignment violates any of the problem constraints, the solution is invalid.
constraints = []


if __name__ == "__main__":

    # inititalize the argument parser so we can get the arguments from the command line
    parser = argparse.ArgumentParser(description = 'take var file, constraint file, and consisitency enforcing procedure')

    # grab the file name for the variables file
    parser.add_argument('varFileName')

    # grab the file name for the constraints file
    parser.add_argument('constraintFileName')

    # grab the consistency enforcing procedure flag. (not implemented at this point, will always be "none"
    parser.add_argument('consistencyEnforcingProcedureFlag')

    # parse the args and put them in args
    args = parser.parse_args()

    # collect all the variables from file
    variables = init.getVariablesFromFile(args.varFileName)

    # collect all the constraints from file
    constraints = init.getConstraintsFromFile(args.constraintFileName)

    # at this point in development, we are not using any consistency enforcing procedures, this feature may be added later.
    none = "none"

    # create the constraint satisfaction problem
    csp = CSP(variables, constraints, none)

    # create the backtracking search instance and feed it the constraint satisfaction problem
    bsearch = Backtracking_Search(csp)

    # start the search at the root of the search tree
    solution = bsearch.backtrack(bsearch.root)

    print "\n\nsolution:" + str(bsearch.solution)











