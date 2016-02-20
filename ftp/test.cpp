#include "ftp_func.h"

int main(){
	DIR* pdir = opendir("./");	
	struct dirent* direntp ;

	std::ostringstream  stream ;
	stream.clear();

	while( (direntp = readdir(pdir)) != NULL ){
		if( strncmp(direntp->d_name, ".", 1) == 0 || strncmp(direntp->d_name,"..", 2) == 0 )
			continue ;
		stream<< direntp->d_name <<'\n';
	}
	std::string content = stream.str();
	std::cout<< content ;
}