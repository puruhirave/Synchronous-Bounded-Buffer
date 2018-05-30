// SyncIO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include "Producer.h"
#include "Consumer.h"


int _tmain(int argc, _TCHAR* argv[])
{

	std::vector<Producer> producers(4);
	std::vector<Consumer> consumers(4);

	size_t i;

	//Create consumers
	for (i = 0; i < consumers.size(); i++)
	{
		consumers[i].setID(i);
		consumers[i].start();
	}

	//Create producers
	for (i = 0; i < producers.size(); i++)
	{
        	std::this_thread::sleep_for(std::chrono::milliseconds(13*i));
		producers[i].setID(i);
		producers[i].start();
	}

	//Join consumers
	for (i = 0; i < consumers.size(); i++)
	{
		consumers[i].JoinToMainThread();
	}


	//Join producers
	for (i = 0; i < producers.size(); i++)
	{
		producers[i].JoinToMainThread();
	}

    	std::cout <<std::endl<< " ... Processed all records..." << std::endl;
	std::cin.get();
	return 0;
}

