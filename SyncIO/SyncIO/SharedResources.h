#ifndef SHARED_RESOURCE
#define SHARED_RESOURCE

static const int MAX_LEN=10;
static const int MAX_RECORDS_TO_PROCESS = 20;
//Shared Resources
int Buffer[MAX_LEN];
int in = 0, out = 0;
int stopCountForProducer = 0;
bool stopConsumerThread = false;

CSemaphore semEmpty(0, MAX_LEN); 
CSemaphore semFull(MAX_LEN, MAX_LEN); //Full
std::mutex mlock;


// Seed with a real random value, if available
std::random_device rd;
// Choose a random mean between 1 and 100
std::default_random_engine e1(rd());
std::uniform_int_distribution<int> uniform_dist(1, 100);


#define PRINT_BUFF(owner)  std::cout << owner << " Prints Buffer =>    [ " ;\
						for(auto res : Buffer) \
							std::cout << res << " "; \
						std::cout << "] \n";

int RandomNumber()
{
	return uniform_dist(e1);
}

#endif
