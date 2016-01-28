__author__ = 'ashley tharp'

import sys
import argparse
import fileinput
from Training_Data import Training_Data
from Tests import Tests

def main():

    data = Training_Data(fileinput.input())

    for cat in data.categories:
        cat.print_me()

if __name__ == '__main__':
    main()