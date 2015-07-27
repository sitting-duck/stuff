READ ME

This program is written in Python so there is no need to compile it.
It can be easily run in a Python IDE of your choice or via the command line.

main.py <file.var> <file.con> <flag>

This class represents a contraint satisfaction problem.  Before we get into the nitty gritty of what's in this class, let's start with a 
high level explanation of what a constraint satisfaction problem is.
Definition:
conceptually, a constraint is a rule or requirement, and we could say, for a example, some set of things, satisfy those constraints.
Example:
 a possible constraint would be "all numbers in this set of numbers must be over 5", and an example set that satisfies that constraint
could be: {6, 100, 32, 41, 99}, and an example set that does not validate that constraint could be {-3, 2}
so now we know conceptually what a constraint is, and what it means to satisfy a constraint, so, it would follow that a constraint
satisfaction problem would concern sets and constraints.

Constraint satisfaction problems are of interest in Artificial Intelligence.
Constraint satisfaction problems often exhibit high complexity, requiring a combination of heuristics and combinatorial search to be
solved in a reasonable amount of time.

Formally, a constraint satisfaction problem is defined as a triple \langle X,D,C \rangle, where [1]
X = \{X_1, \ldots,X_n\} is a set of variables,
D = \{D_1, \ldots, D_n\} is a set of the respective domains of values, and
C = \{C_1, \ldots, C_m\} is a set of constraints.