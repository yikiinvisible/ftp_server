#include "locker.h"
#include "sem.h"
#include "ftp_func.h"
#include <list>
#include <pthread.h>
#include <exception>
#include <iostream>
#include <vector>


class threadpool{
public:
	threadpool( int  , int  );
	~threadpool();
	bool append( ftp_task &request);

	int m_thread_number;
	int m_max_requests;
private:
	static void* worker( void* arg );
	void run();

	
	std::vector<pthread_t> m_threads;
	std::list<ftp_task> m_workqueue;
	locker m_queuelocker;
	sem m_queuestat;
	bool m_stop;
};