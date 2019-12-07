SOURCE=main.cpp Restaurant.cpp Waiter.cpp Menu.cpp MenuItem.cpp Order.cpp Table.cpp Tokenizer.cpp
HEADER=Restaurant.h Waiter.h Menu.h MenuItem.h Order.h Table.h Tokenizer.h

restaurant: $(SOURCE) $(HEADER)
	g++ -Wall -pedantic -std=c++0x -g -o restaurant $(SOURCE)

clean:
	-rm ./*.o
	-rm ./restaurant

