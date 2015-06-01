__author__ = 'ashley'

import sys


class Variable:
	"""All the variables in this engine are propositions which can have the value true or false"""

	def __init__(self, nameArg, negArg):

		# the name of the variable.  Eg. p, controlFlag, isLeaking, etc.
		self.name = nameArg

		# the negation of the variable. If true, then this variable is negated.
		# ie. If true, then the variable p is ~p.
		self.neg = negArg

	def isEquivalent(self, other):
		return self.name == other.name and self.neg == other.neg

	def printVariable(self):
		if self.neg:
			sys.stdout.write((str("~") + self.name))
		else:
			sys.stdout.write(self.name)

	def getVariableAsString(self):
		if self.neg:
			var = str("~" + self.name)
		else:
			var = self.name
		return var

