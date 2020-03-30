public class Decision {
		int row;
		int col;

		Decision(int _row, int _col, Labrinth _maze) {
			if(_row < _maze.rows() - 1 && _col < _maze.cols() - 1) {
				row = _row;
				col = _col;
			} else {
				System.out.println("Error: Invalid Decision value: row: " + row + " col: " + col);
			}
		}


		public void set(int _row, int _col, Labrinth _maze) {
			if(_row < _maze.rows() - 1 && _col < _maze.cols() - 1) {
				row = _row;
				col = _col;
			} else {
				System.out.println("Error: invalid value. Cannot set to: row: " + _row + " col: " + _col);
			}
		}

	}