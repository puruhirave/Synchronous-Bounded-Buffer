# Simulation of Synchronous-Bounded-Buffer
Produce Consumer problem solved with Synchronous Bounded Buffer

This code doesn't implement any Producer/Consumer IPC mechanism purposefully. Because the intent of this program is synchronize the Bounded buffer which is used in Producer-Consumer problem to avoid deadlock and race condition. So main focus is on how Bounded buffer can be synchronized?

* In classical Producer-Consumer problem, if consumer wants to read data from shared memory like fixed length resource buffer, the Consumer cannot read data before the data is produced by Producer. And the Producer cannot overwrite data before the data is consumed by Consumer. It requires signaling mechanism for both Consumer and Producer.
* Also if multiple Producers writing data and multiple Consumer reading data from shared Buffer then there is always race for data. And also it requires proper ordering of read/write operation.

This problem can be solved by using 2 Semaphores. One is for Producer with Max length and one for Consumer with Zero length.

## Shared resources
```C
int Buffer[N];  //Max. N resources.
semWrite(N);
semRead(0);
int in=0, out=0; //Write index and Read index.
Mutex mlock; //For mutual exclusive access to shared buffer
```

## Producer:
```C
Write(data)
{
	//Wait on 'semWrite' semaphore for Consumer to read data if Buffer is Full.
	semWrite.wait(); 
	
	// Wait for mutual exclusive access to buffer
	mlock.lock(); 
	
	//Produce data at Write index and increment index for next write operation
	Buffer[in] = data;      
	in=(in+1)%N;
	
	//Unlock Mutex and signal the 'semRead' semaphore for Consumer to read data.
	Mutex.unlock();  
	semRead.signal();
}
```

## Consumer:
```C
Read(data)
{
	//Wait on 'semWrite' semaphore for Producer to write data if Buffer is Empty.
	semRead.wait(); 
	
	// Wait for mutual exclusive access to buffer
	mlock.lock(); 
	
	//Consume data at Read index and increment index for next read operation  
	data = Buffer[out];    
	out=(out+1)%N;
	
	//Unlock Mutex and signal the 'semWrite' semaphore for Producer to write data.
	Mutex.unlock();   
	semWrite.signal();
}
```
