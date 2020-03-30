
public class Coordinate {

	public int row = -1;
	public int col = -1;

	public Coordinate(int _row, int _col) {
		row = _row;
		col = _col;
	}

	public void print() {
		System.out.println("row: " + row + " col: " + col);
	}

	public String toString() {
		return "row: " + row + " col: " + col;
	}

}