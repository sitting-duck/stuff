__author__ = 'ashley'

# This file will contain what would normally be the main function and other classless functions in a C++ program

import argparse
import init
from CSP import CSP
from Backtracking_Search import Backtracking_Search

#variable and constraint containers
variables = []
constraints = []


if __name__ == "__main__":

    # get args from the command line
    parser = argparse.ArgumentParser(description = 'take var file, constraint file, and consisitency enforcing procedure')
    parser.add_argument('varFileName')
    parser.add_argument('constraintFileName')
    parser.add_argument('consistencyEnforcingProcedureFlag')
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
    bsearch.backtrack(bsearch.root)










