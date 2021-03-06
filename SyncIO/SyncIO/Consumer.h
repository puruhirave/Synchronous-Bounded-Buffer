#include <iostream>
#include <thread>
#include <chrono>
#include "CSemaphore.h"
#include "SharedResources.h"

class Consumer{

	std::thread consumer_thread;
	int m_id;
    public:
	Consumer() : m_id(0) {}
	Consumer(int id) : m_id(id){}
	~Consumer(){}

	void setID(int id){ m_id = id; }

	void start()
	{
		consumer_thread = std::thread(&Consumer::Read, m_id);
	}

	void JoinToMainThread()
	{
		consumer_thread.join();
	}

	static void Read(int id)
	{
		int data = 0;

		while (1)
		{
			semEmpty.wait();
			std::unique_lock<std::mutex> guard(mlock);

            		//Simulation of Consumer thread closing condition.
            		if (semEmpty.GetCount() <= 0 && stopConsumerThread)
			{
                		guard.unlock();
				semFull.notify();
				break;
			}
			
            		data = Buffer[out];
            		Buffer[out] = 0;
			std::cout << "-------- <Consumer  [" << id << "] Received> " << data << " at ReadIndex = " << out << "\n";
			out = (out + 1) % MAX_LEN;
			//PRINT_BUFF("		Consumer");
			semFull.notify();
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			guard.unlock();
		}
	}
};
