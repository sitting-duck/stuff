p: main.o customer.o agent.o semaphores.o threads.o Debug.o common.o info_desk.o announcer.o waiting_room.o agent_line.o
	g++ -lpthread -lrt main.o customer.o agent.o semaphores.o threads.o Debug.o info_desk.o announcer.o waiting_room.o agent_line.o -o p
main.o: main.cpp
	g++ -c main.cpp

customer.o: customer.h customer.cpp
	g++ -c customer.cpp

agent.o: agent.h agent.cpp
	g++ -c agent.cpp

semaphores.o: semaphores.h semaphores.cpp
	g++ -c semaphores.cpp

threads.o: threads.h threads.cpp
	g++ -c threads.cpp

Debug.o: Debug.h Debug.cpp
	g++ -c Debug.cpp

common.o: common.h common.cpp
	g++ -c common.cpp

info_desk.o: info_desk.h info_desk.cpp
	g++ -c info_desk.cpp

announcer.o: announcer.h announcer.cpp
	g++ -c announcer.cpp

waiting_room.o: waiting_room.h waiting_room.cpp
	g++ -c waiting_room.cpp

agent_line.o: agent_line.h agent_line.cpp
	g++ -c agent_line.cpp

clean: 
	rm -rf *.o *.gch *.h~ *.cpp~ makefile~ p
