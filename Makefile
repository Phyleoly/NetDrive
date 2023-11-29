ALL: AppC AppS

AppC: ApplicationClient.o Command.o Client.o
	g++ -o AppC ApplicationClient.o Command.o Client.o
	
AppS: ApplicationServer.o Server.o
	g++ -o AppS ApplicationServer.o Server.o

ApplicationClient.o: ApplicationClient.cpp
	g++ -c ApplicationClient.cpp

ApplicationServer.o: ApplicationServer.cpp
	g++ -c ApplicationServer.cpp

Command.o: Command.cpp 
	g++ -c Command.cpp

Client.o: Client.cpp
	g++ -c Client.cpp

Server.o: Server.cpp
	g++ -c Server.cpp

clean:
	rm -rf *.o AppC AppS