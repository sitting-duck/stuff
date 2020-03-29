import java.util.Random;
import javafx.util.Pair;	

public class Labrinth
{

    private int numRows = 6;    
    private int numColumns = 5; 

    private Cell[][] data = new Cell[numRows][numColumns]; // the actual= labrinth data as 2D array 
  

    public Labrinth() {
    	System.out.println("\tctor");
    } 

    public void init() {

	System.out.println("\tinit");
	
        // fill the entire labrinth with walls (place a 1 into each cell)
        for(int i = 0; i < numRows; i++) {
	     for(int j = 0; j < numColumns; j++) {
	     	data[i][j] = new Cell("1");
	     }
	} 

        // pick a random start point on the first row (row 0) of the array
	Random random_number_generator = new Random(); 
	
	// there are numColumns number of slots in the first row, we use that number - 1 make a suitable range
	// so that we can pick a random array index to be our "Start" cell of the maze
	int column_start = random_number_generator.nextInt(numColumns - 1);
       
        // and mark that node of the labrinth with an "S"	
	data[0][column_start].set("S");

	// generate another random number, so we can do the same thing, but for the "End" cell, in the final row
	int column_end = random_number_generator.nextInt(numColumns - 1);

	// mark the End cell, the exit to the maze with an "E"
	data[numRows - 1][column_end].set("E");
	
	print();

	generateMaze(0, column_start);
 
    }

    public void generateMaze(int row, int col) {
    	//Given a current cell as a parameter,
	//Mark the current cell as empty
	if(data[row][col].get() == "1") {
	    data[row][col].set("0"); 
	}
	
	//While the current cell has any unvisited neighbour cells
	while(
	//Chose one of the unvisited neighbours
	//Remove the wall between the current cell and the chosen cell
	//Invoke the routine recursively for a chosen cell
    }

    public void print() {
	for(int i = 0; i < numRows; i++) {
	    for(int j = 0; j < numColumns; j++) {
   	        System.out.print(data[i][j].get());
	    }
	    System.out.println();
	}
	System.out.println();
    }
 
} 


