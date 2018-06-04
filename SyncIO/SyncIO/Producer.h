#include <iostream>
#include <thread>
#include <chrono>
#include "CSemaphore.h"
#include "SharedResources.h"

class Producer{
	std::thread producer_thread;
	int m_id;
    public:
	Producer() : m_id(0){}
	Producer(int id):m_id(id){}
	~Producer(){}
	void setID(int id){ m_id = id; }
	void start()
	{
		producer_thread = std::thread(&Producer::Write, m_id);
	}

	void JoinToMainThread()
	{
		producer_thread.join();
	}

	static void Write(int id)
	{
		while (1)
		{
			semFull.wait();
			std::unique_lock<std::mutex> guard(mlock);
                        //Simulate to close Writer/Reader Thread after processing MAX 20 records.
                        if (stopCountForProducer >= MAX_RECORDS_TO_PROCESS)
			{
                		stopConsumerThread = true;
                		guard.unlock();
				semEmpty.notify();
				break;
			}
            		Buffer[in] = RandomNumber();
            		std::cout << "  <Producer[" << id << "] written> " << Buffer[in] << " at WriteIndex = " << in << "\n";
			in = (in + 1) % MAX_LEN;
            		stopCountForProducer++;
			PRINT_BUFF("Producer");
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			semEmpty.notify();
			guard.unlock();
		}
		
             	//Gracefull shutdown by notifying Consumer if any data pending to read in Buffer.
        	semEmpty.notify();
	}
};
