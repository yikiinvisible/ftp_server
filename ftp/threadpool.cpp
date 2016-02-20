#include "threadpool.h"

threadpool::threadpool( int thread_number , int max_requests )
: m_thread_number( thread_number), m_max_requests( max_requests), m_stop( false){

	if( (m_thread_number <= 0) || (m_max_requests <=0 ))
		throw std::exception();

	m_threads = std::vector<pthread_t> (thread_number);

	for(int i=0; i< thread_number ;++i ){
		std::cout<<"create the "<<i<<"th thread"<<std::endl;
		if( pthread_create( &m_threads[i], NULL, worker, this )!=0 ){
			throw std::exception();
		}
		if( pthread_detach( m_threads[i] )){
			throw std::exception();
		}
	}
}

threadpool::~threadpool(){
	m_stop = true;
}

bool threadpool::append( ftp_task &request ){

	m_queuelocker.lock();
	if ( m_workqueue.size() > m_max_requests )		
	{
		m_queuelocker.unlock();
		return false;
	}
	m_workqueue.push_back( request );
	m_queuelocker.unlock();
	m_queuestat.post();
	return true;
}

void* threadpool::worker( void* arg ){

	threadpool* pool = ( threadpool* )arg;
	pool->run();
	return pool;
}


void threadpool::run(){

	while( !m_stop ){
		m_queuestat.wait();
		m_queuelocker.lock();
		while( m_workqueue.empty() ){
			m_queuelocker.unlock();
			continue;
		}

		ftp_task request ( m_workqueue.front() );
		m_workqueue.pop_front();
		m_queuelocker.unlock();
		request.process();
	}
}

