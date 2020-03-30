//System.out.println("generateMaze() row: " + row + " col: " + col + " numEmpty: " + numEmpty);
  //   	maze.print();	

  //   	System.out.println("got mah: " + data[row][col].get());

		// //While the current cell is not the end cell and there are less than 15 empty cells (empty as in, not a wall, or start/end cell)
		// boolean done = false;
  //   	while(done == false) { // create path loop

  //   		System.out.println("done: " + done);
  //   		System.out.println("row: " + row);
  //   		System.out.println("col: " + col);
  //   		System.out.println("data[row][col]: " + data[row][col].get());
  //   		scan.nextLine();

		//     // pick a random unvisited neighbor

		//     // whichWay is a number such that:
		//     // 0 = NORTH
		//     // 1 = EAST
		//     // 2 = SOUTH
		//     // 3 = WEST
  //   		int whichWay = -1;

  //   		boolean canMove = false; 
	 //    while(canMove == false) { // choose direction loop
	 //    	whichWay = random_number_generator.nextInt(4);
		// 	//System.out.println("whichWay: " + whichWay);
		// 	//System.out.println("row: " + row);
		// 	//System.out.println("col: " + col);

	 //    	if(whichWay == 0 && row > 0) {        // NORTH

	 //    		if(data[row - 1][col].get() == "1") {
	 //    			if(row == numRows - 1) {
	 //    				data[row - 1][col].set("E");
	 //    				canMove = true;
	 //    				done = true;
	 //    			} else {
	 //    				canMove = true;
		//     			data[row - 1][col].set("0");
		//     			System.out.println("go NORTH");
		//     			generateMaze(row - 1, col, numEmpty + 1);	
	 //    			}
	    			
	 //    		}
		
		// 	} else if(whichWay == 1 && col < numColumns - 1) {        //EAST

		// 		if(data[row][col + 1].get() == "1") {
		// 			if(row == numRows - 1) {
		// 				data[row][col + 1].set("E");
		// 				canMove = true;
	 //    				done = true;
		// 			} else {
		// 				canMove = true;
		// 				data[row][col + 1].set("0");
		// 				System.out.println("go EAST");
		// 				generateMaze(row, col + 1, numEmpty + 1);	
		// 			}

		// 		}
		
		// 	} else if(whichWay == 2 && row < numRows - 1) {        // SOUTH

		// 		if(data[row + 1][col].get() == "1") {
		// 			if(row == numRows - 1) {
		// 				data[row + 1][col].set("E");
		// 				canMove = true;
	 //    				done = true;
		// 			} else {
		// 				canMove = true;
		// 				data[row + 1][col].set("0");
		// 				System.out.println("go SOUTH");
		// 				generateMaze(row + 1, col, numEmpty + 1);	
		// 			}
					
		// 		}
		
		// 	} else if(whichWay == 3 && col > 0) {        // WEST

		// 		if(data[row][col - 1].get() == "1") {
		// 			if(row == numRows - 1) {
		// 				data[row][col - 1].set("E");
		// 				canMove = true;
	 //    				done = true;
		// 			} else {
		// 				canMove = true;
		// 				data[row][col - 1].set("0");
		// 				System.out.println("go WEST");
		// 				generateMaze(row, col - 1, numEmpty + 1);	
		// 			}

		// 		}

		// 	} else {
		// 	    System.out.println("Can't Move");
		// 	    System.out.println("whichWay: " + whichWay);
		// 	    System.out.println("row: " + row);
		// 	    System.out.println("col: " + col); 
		// 	    System.out.println("done: " + done);
		// 	    print();
		// 		canMove = false;
		// 	}
		// } // end choose direction loop

	

	// if there are not at least 15 empty cells, we randomly pick some to make empty until we reach 15