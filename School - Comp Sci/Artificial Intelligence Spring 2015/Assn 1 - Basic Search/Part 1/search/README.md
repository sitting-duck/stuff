Ashley Tharp

### Abstract
This program solves a puzzle using various search techniques. Some search techniques produce optimal solutions, other search techniques produce suboptimal solutions in less time.

#### Description of the puzzle
Example Puzzle: BBBxWWW

The puzzle is a one dimensional set of tiles.  There are an equal number of black tiles and white tiles.  Each tile takes up one slot in the puzzle.  The puzzle has enough slots for an equal number of black tiles and whites and one empty slot.
B - black tile
x - empty slot
W - white tile

####Puzzle Solution:
A puzzle is in a solved state if all the black tiles are to the left of the empty slot, and all the white tiles are to the right of the empty slot. (the implications of this is that the empty slot will always be in the center slot, and that there will always be an odd number of slots.)

There can be more than one possible solution to this puzzle.
	
####Example Solved Puzzles:
	BxW
	BBxWW
	BBBxWWW
	BBBBxWWWW
	
####Example Unsolved Puzzles:
	BWx   *the empty slot is not in the center, the white tile is not to the right of the empty slot
	
	xBBWW *all the black tiles must be to left, all the white tiles must be to the right in order for the puzzle to be solved.
	
	BBxBWWW
	 
####How to solve the puzzle:
The puzzle can be solved by moving the tiles.  

The only possible moves are to select an existing tile and place it into the empty slot (the implication of this is that a new empty slot is created)

If one does not create looping patterns of moves there are a finite amount of solutions to an instance of this puzzle.

Some solutions take less moves than others.  
			
### Source Files:
Problem.h, Problem.cpp
Node.h, Node.cpp
init.cpp
main.cpp

Developed on Windows using Microsoft Visual Studio 2013

## HOW TO RUN:

to run from the command line, navigate to the project folder and run
search [-cost] <BFS|DFS|UCS|GS|A-star> <inputfile>