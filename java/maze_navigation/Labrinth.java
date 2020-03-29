

public class Labrinth
{

    private int numRows = 6;    
    private int numColumns = 5; 

    private Cell[][] data = new Cell[numRows][numColumns]; // the actual= labrinth data as 2D array 
  
    public static void main(String args[]) 
    { 
        System.out.println("Hello, World"); 
    } 

    public void init() {
	
        // fill the entire labrinth with walls (place a 1 into each cell)
        for(int i = 0; i < numRows; i++) {
	     for(int j = 0; j < numColumns; j++) {
	     	data[i][j] = new Cell("1");
	     }
	} 

       // pick a random start point on the first row (row 0) of the array
       
       // and mark that node of the labrinth with an "S"	

 

    }
 
} 

