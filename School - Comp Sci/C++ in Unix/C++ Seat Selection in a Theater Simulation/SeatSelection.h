
#ifndef SEAT_SELECTION_H
#define SEAT_SELECTION_H

class SeatSelection
{
private:
	int numRows;
	int firstRow;
	int numAvailable;
	bool** seats;
public:
	SeatSelection();
	SeatSelection(int, int);
	~SeatSelection();

	void SetSeatsToTaken(int _row, int _column, int _numPpl);
	bool seatParty(int);
	void printSection();
	int getNumAvailable();
	void printTicket(int _row, int _column, int _numPpl);
	void printTicket(int* _row, int* _column, int _numPpl);
};

#endif
