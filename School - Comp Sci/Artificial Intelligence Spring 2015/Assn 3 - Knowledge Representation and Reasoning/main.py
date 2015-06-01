__author__ = 'ashley'

"""
In order to understand this program the reader should first be familiar with the basics of propositional logic,
predicate logic, and proof theory.

This program is a theorem prover for a clause logic using the Resolution Principle.  Well formed sentences in this
logic are clauses.  These clauses will be using disjunctive form instead of implicative form since this form is more
suitable for automatic manipulation.

1. (p -> q) is equivalent to (~p OR q)
2. (~(p OR q)) is equivalent to (~p OR ~q)
3. (~(p OR q)) is equivalent to (~p OR ~q)
4. ((p OR q) OR . . .) is equivalent to (p OR q OR . . .)
5. ((p OR q) OR . . .) is equivalent to (p OR q OR . . .)
6. (~(~p)) is equivalent to p

A clause:
    literal OR literal ... OR literal OR literal

A literal:
    Atom OR ~Atom
    note: ~ stands for negation

An atom:
    true OR false OR p OR q ...

The proof theory of the clause logic contains only the resolution rule:

    ~a OR l1 OR . . . OR ln,
     a OR L1 OR . . . OR Lm
________________________________________
l1 OR . . . OR ln OR L1 OR . . . OR Lm

*notice that the 'a' variable has been cancelled out

"""

import sys
import argparse
import init
import copy
from Clause import Clause
from Variable import Variable

# the initial knowledge base from the file
KB = []

#the set of clauses created during the resolution process
newClauses = []


def getComplimentaryVars(Ci, Cj):
	# eg. p and ~p are complimentary variables.
	# resolving p OR q with z OR ~p gives q OR z
	# note: order does not matter because disjunction is commutatative
	# note: it is possible that there is more than one complimentary variable for
	# each pair of clauses. eg. p OR q and ~p OR ~q
	complimentaryVars = []

	#find all the complimentary variables in the clause pair
	for vari in Ci.vars:
		for varj in Cj.vars:
			if vari.name == varj.name and vari.neg != varj.neg:
				complimentaryVars.append(vari.name)
	return complimentaryVars


#def removeDuplicates(varList):
#    seenVars = []
#    varListCopy = copy.deepcopy(varList)
#    for var in varList:
#        if hasVar(var, seenVars) == False:
#            seenVars.append(copy.deepcopy(var))
#        else:
#            varListCopy.remove(var)
#    varList = []
#    varList = copy.deepcopy(varListCopy)
#    return varList

def removeDuplicates(varList):
	noDupes = []
	for var in varList:
		if hasVar(var, noDupes) == False:
			noDupes.append(var)
	return noDupes


def hasVar(var, varList):
	for item in varList:
		if var.isEquivalent(item):
			return True
	return False


def getDuplicates(Ci, Cj):
	duplicates = []
	for vari in Ci.vars:
		for varj in Cj.vars:
			if vari.name == varj.name and vari.neg == varj.neg:
				duplicates.append(copy.deepcopy(vari))

	if len(duplicates) != 0:
		print "got dups:",
		for dup in duplicates:
			dup.printVariable()
			print " ",

		print ""
	return duplicates


def resolve(Ci, Cj):
	print "resolve",
	Ci.printClause()
	print " and",
	Cj.printClause()
	print " got:",

	#print""
	#print "Ci:",
	#Ci.printClause()
	#print""
	#Ci.vars = removeDuplicates(Ci.vars)
	#print "after remove dups:",
	#Ci.printClause()
	#print""

	#print "Cj:",
	#Cj.printClause()
	#print ""
	#print "after remove dups:",
	#Cj.printClause()
	#print""

	Cj.vars = removeDuplicates(Cj.vars)

	# eg. p and ~p are complimentary vars. The new resolved clause will not have p OR ~p.
	complimentaryVars = getComplimentaryVars(Ci, Cj)
	compVar = complimentaryVars[0]

	#make a new clause that is void of the complimentary variables and duplicates
	varsInCi = copy.deepcopy(Ci.vars)
	varsInCj = copy.deepcopy(Cj.vars)
	for var in varsInCi:
		if var.name == compVar:
			varsInCi.remove(var)
	for var in varsInCj:
		if var.name == compVar:
			varsInCj.remove(var)

	#new vars has the set of vars for the new clause.  All complimentary vars have been removed
	newVars = varsInCi + varsInCj
	newVars = removeDuplicates(newVars)

	parents = []
	parents.append(Ci.number)
	parents.append(Cj.number)
	#make a new clause from the two clauses that we have resolved together
	#note: clause number is set to 0, we assign real clause number when we add it to the KB
	resolvent = Clause(0, newVars, parents)

	resolvent.printClause()
	print ""

	return resolvent


def isInKB(newClause):
	for clause in KB:
		if clause.isEquivalent(newClause):
			return True
	return False


def isInNewClauses(newClause):
	for clause in newClauses:
		if clause.isEquivalent(newClause):
			return True
	return False


def getProofTree():
	# the clause with a single variable named "False" will be the root of the proof tree.
	# we are going to grab the parents of that node, all the way up to the leaves.
	# If it helps you can think of this as an upside down tree with the root at the bottom.

	tree = []

	for clause in KB:
		if clause.vars[0].name == "False":
			root = clause

	tree.append(copy.deepcopy(root))

	currentNode = root

	tree = DFSProofTree(tree, currentNode)



	#print the proof tree
	print "proof tree"
	for clause in tree:
		clause.printClause()
		print ""
	return tree


def outputToFile(filename, tree):
	filename = filename[:-3]
	file = open(filename + ".out", 'w')
	for clause in tree:
		file.write(clause.getClauseAsString())
		file.write('\n')
	file.close()


def DFSProofTree(tree, currentNode):
	for parent in currentNode.parents:
		for clause in KB:
			if clause.number == parent:
				currentNode = KB[parent - 1]
				tree.append(copy.deepcopy(currentNode))
				DFSProofTree(tree, currentNode)
				break

	# sort the proof tree by clause number
	sortedTree = sorted(tree, key=lambda clause: clause.number)
	return sortedTree

# main function
if __name__ == "__main__":

	# here we get the args from the command line.  There is only one arg for this program, which is the name of the
	# file that will contain all the constraints for the initial knowledge base.  Basically we are going to initialize
	# the knowledge base with all the "knowledge" from this file.  "Knowledge" is in the form of clauses.

	commandLineArgumentParser = argparse.ArgumentParser()
	commandLineArgumentParser.add_argument('KBFileName')
	commandLineArgs = commandLineArgumentParser.parse_args()

	# pass the file name we just to the init func getClausesFromFile which will populate our knowledge base with
	# clauses
	KB = init.getClausesFromFile(commandLineArgs.KBFileName)

	while True:
		for Ci in KB:
			for Cj in KB:
				if Ci != Cj:
					if len(getComplimentaryVars(Ci, Cj)) != 0:
						resolvent = resolve(Ci, Cj)

						# check to sees if the resolvent is the empty clause
						# if we have an empty clause, then alpha is valid var in alpha is accounted for
						# not a single var in ~alpha is satisfiable because it has been cancelled out
						if len(resolvent.vars) == 0:
							print "alpha is valid\n"
							falseVar = Variable("False", False)
							falseVars = []
							falseVars.append(falseVar)
							emptyClause = Clause(len(KB) + 1, falseVars, resolvent.parents, )
							KB.append(copy.deepcopy(emptyClause))
							print "the knowledge base"
							for clause in KB:
								clause.printClause()
								print ""
							print ""
							tree = getProofTree()
							outputToFile(commandLineArgs.KBFileName, tree)
							sys.exit(0)

						#if this clause is not already defined in the list of new clauses, then
						# we add it to the set
						if isInNewClauses(resolvent) == False:
							newClauses.append(copy.deepcopy(resolvent))

		#print "got new clauses:"
		#for new in newClauses:
		#    new.printClause()
		#    print ""
		#print ""

		# make sure that resolvent is not already defined in KB
		isSubset = True
		for new in newClauses:
			if isInKB(new) == False:
				isSubset = False
				new.number = len(KB) + 1
				KB.append(copy.deepcopy(new))

		if isSubset:
			print "Failure"
			filename = commandLineArgs.KBFileName[:-3]
			file = open(filename + ".out", 'w')
			file.write("Failure\n")
			file.close()
			tree = getProofTree()
			outputToFile(commandLineArgs.KBFileName, tree)
			for clause in KB:
				clause.printClause()
				print ""
				sys.exit(0)