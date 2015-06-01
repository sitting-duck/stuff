
both: ./client_machine/client ./server_machine/server

./client_machine/client: ./client_machine/client.c
	gcc ./client_machine/client.c -lpthread -Werror -o ./client_machine/client

./server_machine/server: ./server_machine/server.c
	gcc ./server_machine/server.c -lpthread -Werror -o ./server_machine/server

.PHONY: clean
clean: 
	rm -rf ./client_machine/*~ ./server_machie/*~ ./client_machine/*.gch ./server_machine/*.gch ./client_machine/.*.swp  ./server_machine/.*.swp ./client_machine/client ./server_machine/server ./client_machine/*.o ./server_machine/*.o ./client_machine/east.jpg ./client_machine/west.jpg ./client_machine/south.jpg ./client_machine/north.jpg ./*~
