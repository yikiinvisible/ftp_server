#include "tcp_socket.h"
#include "threadpool.h"

int main(int argc, char** argv){
	tcp_socket server;
	server.create();
	server.bind( argv[1], atoi(argv[2]) );
	server.listen();
	struct sockaddr* client_address;
	threadpool poll(10, 100);

	while(1){
		int connfd = server.accept( client_address );
		ftp_task task(connfd);
		poll.append( task );
	}

	return 0;
}