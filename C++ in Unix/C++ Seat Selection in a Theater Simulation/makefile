CFLAGS=-Wall 

seats: theater.cpp SeatSelection.cpp SeatSelection.h
	g++ $(CFLAGS) -o seats SeatSelection.cpp theater.cpp

clean:
	rm ./seats
	rm ./*.o
