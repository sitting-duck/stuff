import java.util.Random;
import java.util.Scanner;

public class Labrinth
{

	private int numRows = 6;    
	private int numColumns = 5;
	private int minEmpty = 15;

	private Coordinate start;

    private Cell[][] data = new Cell[numRows][numColumns]; // the actual= labrinth data as 2D array 

    private Random random_number_generator;
    private Scanner scan;

    public Labrinth() {

    	System.out.println("\tinit");

    	scan = new Scanner(System.in);

        // fill the entire labrinth with walls (place a 1 into each cell)
    	for(int i = 0; i < numRows; i++) {
    		for(int j = 0; j < numColumns; j++) {
    			data[i][j] = new Cell("1");
    		}
    	} 

        // pick a random start point on the first row (row 0) of the array
    	random_number_generator = new Random(); 

	// there are numColumns number of slots in the first row, we use that number - 1 make a suitable range
	// so that we can pick a random array index to be our "Start" cell of the maze
    	int column_start = random_number_generator.nextInt(numColumns - 1);

        // and mark that node of the labrinth with an "S"	
    	data[0][column_start].set("S");
    	start = new Coordinate(0, column_start);

    }

	public int rows() {
		return numRows;
	}

	public int cols() {
		return numColumns;
	}

	public String at(int _row, int _col) {
		if (_row < numRows - 1 || _col < numColumns - 1) {
			System.out.println("Error: invalid coordinate!!");
			return "";
		} else {
			return data[_row][_col].get();
		}
	}

	public boolean validRow(int _row) {
		boolean valid = _row > 0 && (_row < numRows - 1);
		System.out.println("validRow(): row: " + _row + " " + valid);
		return valid;
	}

	public boolean validCol(int _col) {
		boolean valid = _col > 0 && (_col < numColumns -1);
		System.out.println("validCol: col: " + _col + " " + valid);
		return valid;
	}

	public boolean canGoHere(Coordinate _coordinate) {
		boolean canGo = validRow(_coordinate.row) && validCol(_coordinate.col);
		System.out.println("\tcanGoHere: " + canGo);
		return validRow(_coordinate.row) && validCol(_coordinate.col);
	} 

	public boolean isWall(Coordinate _coordinate) {
		System.out.println("isWall(): " + data[_coordinate.row][_coordinate.col].get() + " " + data[_coordinate.row][_coordinate.col].get() == "1");
		return data[_coordinate.row][_coordinate.col].get() == "1";
		//return true;
	}

	public boolean isEmpty(Coordinate _coordinate) {
		return data[_coordinate.row][_coordinate.col].get() == "0";
	}

	public Coordinate start() {
		return start;
	}

	public boolean canEndPath(Coordinate _coordinate) {
		return _coordinate.row == numRows - 1;
	}

	public boolean isValid(int _decision, Coordinate _coordinate) {
		System.out.println("isValid(): decision: " + _decision + " coordinate: ");
		_coordinate.print();

		if(_decision == 0) {
			boolean canBreakNorth = canBreakNorth(_coordinate);
			System.out.println("canBreakNorth: " + canBreakNorth);
			return canBreakNorth;
		} else if(_decision == 1) {
			boolean canBreakEast = canBreakEast(_coordinate);
			System.out.println("canBreakEast: " + canBreakEast);
			return canBreakEast;
		} else if(_decision == 2) {
			boolean canBreakSouth = canBreakSouth(_coordinate);
			System.out.println("canBreakSouth: " + canBreakSouth);
			return canBreakSouth;
		} else if(_decision == 3) {
			boolean canBreakWest = canBreakWest(_coordinate);
			System.out.println("canBreakWest: " + canBreakWest);
			return canBreakWest;
		} else {
			return false;
		}
	}

	public boolean canBreakNorth(Coordinate _coordinate) {
		System.out.println("cangoherr: " + canGoHere(new Coordinate(_coordinate.row - 1, _coordinate.col)));

		Coordinate newCoord = new Coordinate(_coordinate.row - 1, _coordinate.col);
		return canGoHere(newCoord) && isWall(newCoord);
	}

	public Coordinate getNorth(Coordinate _coordinate) {
		return new Coordinate(_coordinate.row - 1, _coordinate.col);
	}

	public boolean canBreakEast(Coordinate _coordinate) {
		System.out.println("cangoherr: " + canGoHere(new Coordinate(_coordinate.row, _coordinate.col + 1)));

		Coordinate newCoord = new Coordinate(_coordinate.row, _coordinate.col + 1);
		return canGoHere(newCoord) && isWall(newCoord);
	}

	public Coordinate getEast(Coordinate _coordinate) {
		return new Coordinate(_coordinate.row, _coordinate.col + 1);	
	}

	public boolean canBreakSouth(Coordinate _coordinate) {
		Coordinate newCoord = new Coordinate(_coordinate.row + 1, _coordinate.col);
		return canGoHere(newCoord) && isWall(newCoord);
	}

	public Coordinate getSouth(Coordinate _coordinate) {
		return new Coordinate(_coordinate.row + 1, _coordinate.col);	
	}

	public boolean canBreakWest(Coordinate _coordinate) {
		Coordinate newCoord = new Coordinate(_coordinate.row, _coordinate.col -1);
		return canGoHere(newCoord) && isWall(newCoord);
	}

	public Coordinate getWest(Coordinate _coordinate) {
		return new Coordinate(_coordinate.row, _coordinate.col - 1);	
	}

	public boolean canBreakAWall(Coordinate _coordinate) {
		return  canBreakNorth(_coordinate) || 
				canBreakEast(_coordinate)  || 
				canBreakSouth(_coordinate) ||
				canBreakWest(_coordinate);
	}

	public Coordinate nextChoiceAsCoordinate(int _decision, Coordinate _coordinate) {

		//     // _decision is a number such that:
		//     // 0 = NORTH
		//     // 1 = EAST
		//     // 2 = SOUTH
		//     // 3 = WEST

		if(_decision == 0) {        // NORTH
			return getNorth(_coordinate);
		} else if(_decision == 1) { // EAST
				return getEast(_coordinate);
		} else if(_decision == 2) { // SOUTH
			return getSouth(_coordinate);
		} else { 				   // WEST
			return getWest(_coordinate);
		}
    
	}

	public void endPath(Coordinate _coordinate) {
		data[_coordinate.row][_coordinate.col].set("E");
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


