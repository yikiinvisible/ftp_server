#include <pthread.h>
#include <exception>

class locker
{
public:
	locker(){
		if ( pthread_mutex_init( &m_mutex, NULL )!=0 )
		{	
			throw std::exception();
		}
	}
	~locker(){
		pthread_mutex_destroy( &m_mutex);
	}
	bool lock(){
		return pthread_mutex_lock( &m_mutex);
	}
	bool unlock(){
		return pthread_mutex_unlock( &m_mutex);
	}
private:
	pthread_mutex_t m_mutex;
};
