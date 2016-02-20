all: server

INCLUDE = .
server: threadpool.o server.o  tcp_socket.o ftp_func.o
	g++ -o server threadpool.o server.o tcp_socket.o ftp_func.o -lpthread

ftp_func.o: ftp_func.cpp ftp_func.h
	g++ -I$(INCLUDE) -c ftp_func.cpp 

threadpool.o: threadpool.cpp threadpool.h sem.h locker.h ftp_func.h 
	g++ -I$(INCLUDE) -c threadpool.cpp 

tcp_socket.o: tcp_socket.cpp tcp_socket.h
	g++ -I$(INCLUDE) -c tcp_socket.cpp 

server.o: threadpool.h server.cpp tcp_socket.h threadpool.h
	g++ -I$(INCLUDE) -c server.cpp



make clean:
	-rm *.o
