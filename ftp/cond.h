class cond
{
public:
	cond(){
		if ( pthread_mutex_init( &m_mutex, NULL)!=0 )		
		{	
			throw std::exception();
		}
		if ( pthread_cond_init( &m_cond, NULL)!=0 )
		{
			pthread_mutex_destory( &m_mutex);
			throw std::exception();
		}
	}
	~cond(){
		pthread_mutex_destory( &m_mutex);
		pthread_cond_destory( &m_cond);
	}
	bool wait(){
		int ret = 0;
		pthread_mutex_lock( &m_mutex);
		ret = pthread_cond_wait( &m_cond, &m_mutex);
		return ret == 0;
	}
	bool signal(){
		return pthread_cond_signal( &m_cond) ==0;
	}
private:
	pthread_mutex_t m_mutex;
	pthread_cond_t  m_cond;
};