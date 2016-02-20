#include "tcp_server.h"
#include <string>
int main(int argc, char** argv){
	tcp_socket client( argv[1], atoi(argv[2]) );
	client.connect();
	std::string command;
	char recv_buf[1024];
	bzero(recv_buf,0);
	while( cin >> command ){
		send( client.get_fd(), command.c_str(), command.size(), 0 );

		while ( (recv( client.get_fd(), recv_buf, 1023, 0 )) >0 ){
			puts()
		}
	}

}