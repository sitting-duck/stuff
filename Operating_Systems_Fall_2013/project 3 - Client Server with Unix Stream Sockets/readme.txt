This folder is called project3
this folder has the makefile in it.

This folder contains two folders.
client_machine and server_machine
these two folders emulate a situation as if the client and the server were
actually two seperate machines.

To start the client program you will need to call client CS1 <port number>
inside of the client_machine folder.

To start the server program you will need to call server <port number> inside
of the server_machine folder.

As mentioned in the assignment specification, the server must be running when
the client is started.

you can type "make" in the project 3 folder to compile the entire project.
You can type "make clean" to clean the project.  This will remove all .o
files, executables, and any image files that the client recreated on its side.
That way by typing "make clean" in the project3 folder you can start over any
time you want.

you can look inside client_machine to grab the transferred image files and see
that they were transferred successfully.  

Do make sure you don't try to do "make" inside the client_machine or
server_machine folders.  You'll want to be in the root folder for this
project, the project3 folder.
