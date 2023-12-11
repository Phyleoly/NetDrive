ALL: AppC AppS

AppC: ApplicationClient.o Command.o ThreadPool.o
	g++ -o AppC ApplicationClient.o Command.o ThreadPool.o
	
AppS: ApplicationServer.o ThreadPool.o Command.o Server.o
	g++ -o AppS ApplicationServer.o ThreadPool.o Command.o Server.o

ApplicationClient.o: ApplicationClient.cpp
	g++ -c ApplicationClient.cpp

ApplicationServer.o: ApplicationServer.cpp
	g++ -c ApplicationServer.cpp

Client.o: Client.cpp
	g++ -c Client.cpp

Command.o: Command.cpp 
	g++ -c Command.cpp

Server.o: Server.cpp
	g++ -c Server.cpp

File.o: File.cpp
	g++ -c File.cpp

ThreadPool.o: ThreadPool.cpp
	g++ -c ThreadPool.cpp

clean:
	rm -rf *.o AppC AppS