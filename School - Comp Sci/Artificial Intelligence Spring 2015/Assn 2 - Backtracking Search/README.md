***Abstract/Conceptual Explanation***

The program solves a constraint satisfaction problem.  This program uses a backtracking search to find a set of variables that satisfies all the problem constraints.  

****Example****
Imagine that there are 2 variables, A, and B. A, and B, are integer variables. There is one constraint.  The constraint is that A > B. The domain of A is {1, 2} The domain of B is {1, 2}.  A possible valid solution to this problem is {A=2, B=1}. The output for this program with this problem setup would be:

```
currentVar is : A
A>B
value effects: [('2', 1), ('1', 2)]
current child assn: {'A': '2'}
currentVar is : B
B<A
value effects: [('1', 1), ('2', 2)]
current child assn: {'A': '2', 'B': '1'}
valid solution: {'A': '2', 'B': '1'}
current child assn: {'A': '1'}
currentVar is : B
B<A
value effects: [('1', 1), ('2', 2)]
current child assn: {'A': '1', 'B': '1'}
current child assn: {'A': '1', 'B': '2'}


solution:{'A': '2', 'B': '1'}
```

Constraint satisfaction problems are of interest in Artificial Intelligence.
Constraint satisfaction problems often exhibit high complexity, requiring a combination of heuristics and combinatorial search to be
solved in a reasonable amount of time.

**Running the Program**
Written in Python
Developed with Pycharm IDE on Windows 8.

It can be easily run in a Python IDE of your choice or via the command line if you have Python installed.
(note: for some reason this program executes lightning fast in Pycharm, but really slow on the command line, I still haven't gotten to the
bottom of this)

main.py <file.var> <file.con> <flag>

<file.var> is a file containing all the problem variables. A .var file will be formatted like this:

A: 1 2 3 4 5
B: 1 2 3 4 5
C: 1 2 3 4 5
D: 1 2 3 4 5
E: 1 2 3
F: 1 2 

The first token is the name of the variable followed by a colon.  All tokens remaining on the same line are values in the domain of that variable.  In the example above, variable A has a domain of {1, 2, 3, 4, 5} ie. A can be assigned any one of those values.

<file.con> is a file containing all of the program constraints.  A .con file will be formatted like this:

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

<flag> - this third argument is a consistency enforcing procedure flag.  At the time of this writing, this feature has not been added, so this parameter will always be "none"

