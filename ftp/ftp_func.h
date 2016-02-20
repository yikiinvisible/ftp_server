#include <fstream>
#include <string>
#include <sstream>
#include <dirent.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>


class ftp_task{
public:
	ftp_task(int fd):m_client_fd(fd){}
	void process();
private:
	void cd(std::string);
	void ls();
	void puts(std::string);
	void gets(std::string);
	int m_client_fd;
};