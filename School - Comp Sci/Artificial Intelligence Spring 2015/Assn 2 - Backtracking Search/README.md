***Abstract/Conceptual Explanation***

The program solves a constraint satisfaction problem.  This program uses a backtracking search to find a set of variables that satisfies all the problem constraints.  

From Wikipedia: 
Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each partial candidate c ("backtracks") as soon as it determines that c cannot possibly be completed to a valid solution.
The classic textbook example of the use of backtracking is the eight queens puzzle, that asks for all arrangements of eight chess queens on a standard chessboard so that no queen attacks any other. In the common backtracking approach, the partial candidates are arrangements of k queens in the first k rows of the board, all in different rows and columns. Any partial solution that contains two mutually attacking queens can be abandoned, since it cannot possibly be completed to a valid solution.
Backtracking can be applied only for problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution. It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.

****Example****
Imagine that there are 2 variables, A, and B. A, and B, are integer variables. There is one constraint.  The constraint is that A > B. The domain of A is {1, 2, 3} The domain of B is {1, 2}. 

The solutions to this problem setup would be:

```
{'A': '3', 'B': '1'}
{'A': '2', 'B': '1'}
{'A': '3', 'B': '2'}
```

The output for this program with this problem setup would be:

```
currentVar is : B
B<A
value effects: [('1', 1), ('2', 2)]
children created: 
{'B': '1'}
{'B': '2'}
currentVar is : A
A>B
value effects: [('3', 1), ('2', 2), ('1', 3)]
children created: 
{'A': '3', 'B': '1'}
{'A': '2', 'B': '1'}
{'A': '1', 'B': '1'}
valid solution: {'A': '3', 'B': '1'}
valid solution: {'A': '2', 'B': '1'}
currentVar is : A
A>B
value effects: [('3', 1), ('2', 2), ('1', 3)]
children created: 
{'A': '3', 'B': '2'}
{'A': '2', 'B': '2'}
{'A': '1', 'B': '2'}
valid solution: {'A': '3', 'B': '2'}

solutions found:
solution:{'A': '3', 'B': '1'}
solution:{'A': '2', 'B': '1'}
solution:{'A': '3', 'B': '2'}
```

Constraint satisfaction problems are of interest in Artificial Intelligence.
Constraint satisfaction problems often exhibit high complexity, requiring a combination of heuristics and combinatorial search to be
solved in a reasonable amount of time.

**Running the Program**
Written in Python
Developed with Pycharm IDE on Windows 8.

It can be easily run in a Python IDE of your choice or via the command line if you have Python installed.

**Command Line Invokation:** main.py <file.var> <file.con> <flag>

**\<file.var\>** is a file containing all the problem variables. A .var file will be formatted like this:

A: 1 2 3 4 5
B: 1 2 3 4 5
C: 1 2 3 4 5
D: 1 2 3 4 5
E: 1 2 3
F: 1 2 

The first token is the name of the variable followed by a colon.  All tokens remaining on the same line are values in the domain of that variable.  In the example above, variable A has a domain of {1, 2, 3, 4, 5} ie. A can be assigned any one of those values.

**\<file.con\>** is a file containing all of the program constraints.  A .con file will be formatted like this:

A > B
B > F
A > C
C > E
A > D
D = E
A ! B


The valid constraint operators are <, >, !, and =.
All constraints in this program are binary constraints to make computation simpler.
It is possible for a constraint to contain more than two variables, but it is also possible to break a multi-variable constraint into several binary constraints.

**\<flag\>** - this third argument is a consistency enforcing procedure flag.  At the time of this writing, this feature has not been added, so this parameter will always be "none"

***Room for Improvement***
At its current state it should work with correct input for any CSP.
However, I could add some checks for improper input to make sure for example the constraints file does not reference any variables not defined in the variables file.
