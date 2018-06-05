# Simulation of Synchronous-Bounded-Buffer
Produce Consumer problem solved with Synchronous Bounded Buffer

The intent of this program is to synchronize the Bounded buffer which is used in Producer-Consumer problem to avoid deadlock and race condition. So main focus is on how Bounded buffer can be synchronized? This code does not covers real Producer/Consumer process creation part like fork() or Shared memory creating system calls purposefuly.

* In classical Producer-Consumer problem, if consumer wants to read data from shared memory like fixed length resource buffer, the Consumer cannot read data before the data is produced by Producer. And same way the Producer cannot overwrite data before the data is consumed by Consumer. It requires signaling mechanism for both Consumer and Producer.
* Also if multiple Producers writing data and multiple Consumers reading data from shared Buffer then there is always race for data. And also it requires proper ordering of read/write operation.

This problem can be solved by using 2 Semaphores. One is for Producer with Max length and one for Consumer with Zero length.
Following is the psudo code of important parts of this program.

## Shared resources
```C
int Buffer[N];  //Max. N resources.
CSemaphore semEmpty(N);
CSemaphore semFull(0);
int in=0, out=0; //Write index and Read index.
Mutex mlock; //For mutual exclusive access to shared buffer
```

## Producer:
Consider there are multiple Producers writting in to the Buffer one at a time.
```C
Producer
{
	//Each Producer writes data in tight loop.
    	Write(int data)
    	{
		//Wait on 'semFull' semaphore for Consumer to read data if Buffer is Full.
		semFull.wait(); 
	
		// Get mutual exclusive access to buffer
		mlock.lock(); 
	
		//Produce data at Write index and increment index for next write operation
		Buffer[in] = data;      
		in=(in+1)%N;
	
		//Unlock Mutex and signal the 'semRead' semaphore for Consumer to read data.
		Mutex.unlock();  
		semEmpty.signal();
    	}
}	
```

## Consumer:
```C
Consumer
{
	//Each Consumer reads data from Buffer in tight loop.
	Read(int & readData)
	{
		//Wait on 'semEmpty' semaphore for Producer to write data if Buffer is Empty.
		semEmpty.wait(); 

		// Get mutual exclusive access to buffer
		mlock.lock(); 

		//Consume data at Read index and increment index for next read operation  
		readData = Buffer[out];    
		out=(out+1)%N;

		//Unlock Mutex and signal the 'semWrite' semaphore for Producer to write data.
		Mutex.unlock();   
		semFull.signal();
	}
}
```

For better understanding, maximum 20 records are used to be processed by 4 different Producers and Consumers. See the screen shot of executable below,

![boundebufferoutput](https://user-images.githubusercontent.com/6056609/40879947-3a35ba78-66c6-11e8-80fa-958867de0fdc.png)



