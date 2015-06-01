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

    # initialize some stuff
    variables = init.getVariablesFromFile(args.varFileName)
    constraints = init.getConstraintsFromFile(args.constraintFileName)
    none = "none"
    csp = CSP(variables, constraints, none)
    bsearch = Backtracking_Search(csp, args.consistencyEnforcingProcedureFlag)

    # start the search
    bsearch.backtrack(bsearch.root)










