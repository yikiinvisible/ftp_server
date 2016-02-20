#include "ftp_func.h"

void ftp_task::ls(){

	DIR* pdir = opendir("/home/bono/Desktop/Lib");	
	struct dirent* direntp ;

	std::ostringstream  stream ;
	stream.clear();

	while( (direntp = readdir(pdir)) != NULL ){
		if( strncmp(direntp->d_name, ".", 1) == 0 || strncmp(direntp->d_name,"..", 2) == 0 )
			continue ;
		stream<< direntp->d_name <<'\n';
	}
	std::string content = stream.str();

	closedir( pdir );

	send( m_client_fd, content.c_str(), content.size(), 0 );

}

void ftp_task::cd( std::string filename ){
	chdir( filename.c_str() );
}

void ftp_task::gets( std::string filename ){
	std::ifstream in;
	in.clear();
	in.open( filename.c_str() );

	std::string content;
	while( in >> content ){
		send( m_client_fd, content.c_str(), content.size(), 0 );
	}
	in.close();
}

void ftp_task::puts( std::string filename ){
	std::ofstream out;
	out.open(filename.c_str() );

	char recv_buf[1024];
	bzero(recv_buf,0);
	while( recv( m_client_fd, recv_buf, 1023 ,0 ) ){
		std::string content = recv_buf;
		out<<content;
	}

	out.close();

}

void ftp_task::process(){
	char recv_buf[1024];
	chdir("/home/bono/Desktop/Lib" );
	while(1){
		recv( m_client_fd, recv_buf, 1023 ,0 );

		std::string command = recv_buf;
		std::istringstream stream( command );
		std::string word;
		stream >> word ;

		if( word == "cd"){
			stream >> word;
			cd( word );
		}
		else if( word == "ls" ){
			ls();
		}
		
		else if( word == "gets" ){
			while( stream >> word )
				gets(word);
		}
		else if( word == "puts"){
			while( stream >> word )
				puts(word);
		}
	} 
}
