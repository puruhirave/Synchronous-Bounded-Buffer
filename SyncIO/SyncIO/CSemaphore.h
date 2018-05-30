#ifndef SEMAPHORE
#define SEMAPHORE

#include <mutex>
#include <condition_variable>

class CSemaphore{
	int m_count;
	int m_maxCount;
	std::mutex m_lock;
	std::condition_variable m_cv;
public:
    	CSemaphore() { m_count = 0; m_maxCount = 0; }
	CSemaphore(int cnt , int maxcount ) : m_count(cnt)
	{
		if (maxcount < cnt)
			m_maxCount = cnt;
		else
			m_maxCount = maxcount;
	}

	CSemaphore(const CSemaphore& ) = delete;
	CSemaphore& operator=(const CSemaphore& ) = delete;

	void notify()
	{
		std::unique_lock<std::mutex> lock(m_lock);
		if (m_count < m_maxCount)
		{
			m_count++;
			lock.unlock();
		}
		m_cv.notify_one();
	}
	int GetCount(){ return m_count; }
	void wait()
	{
		std::unique_lock<std::mutex> lock(m_lock);
		m_cv.wait(lock, [&](){ return m_count != 0; });
		m_count--;
		lock.unlock();
	}

	//~CSemaphore(){}
};

#endif
