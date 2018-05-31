# Simulation of Synchronous-Bounded-Buffer
Produce Consumer problem solved with Synchronous Bounded Buffer

This code doesn't implement any Producer/Consumer IPC mechanism purposefully. Because the intent of this program is synchronize the Bounded buffer which is used in Producer-Consumer problem without deadlock or race condition. So main focus is on how Bounded buffer can be synchronized?

*In classical Producer-Consumer problem, if consumer wants to read data from shared memory like fixed length resource buffer, the Consumer cannot read data before the data is produced by Producer. And the Producer cannot overwrite data before the data is consumed by Consumer. It requires signaling mechanism for both Consumer and Producer.
Also if multiple Producers writing data and multiple Consumer reading data from shared Buffer then there is always race for data. And also it requires proper ordering of read/write operation.
This problem can be solved by using two Semaphores one is for Producer with Max length and one for Consumer with Zero length.

*Shared resources
Buffer[N];  //Max. N resources.
semWrite(N);
semRead(0);
in=0, out=0; //Write index and Read index.
Mutex mlock; //For mutual exclusive access to shared buffer

# Producer:
Send(data)
{
	semWrite.wait(); //Wait for Consumer to read data if Buffer is Full.
	mlock.lock(); // Wait for mutual exclusive access to buffer
	//Produce data at Write index and increment index for next write operation   
	Buffer[in] = data;   
	in=(in+1)%N;
	//Unlock Mutex and signal Consumer to read data by semRead.
	Mutex.unlock();
	semRead.signal();
}

# Consumer:

Recieve(data)
{
	semRead.wait(); //Wait for Producer to write data if Buffer is Empty.
	mlock.lock(); // Wait for mutual exclusive access to buffer
	//Consume data at Read index and increment index for next read operation   
	data = Buffer[out] =;   
	out=(out+1)%N;
	//Unlock Mutex and signal Producer to write data by semWrite.
	Mutex.unlock();
	semWrite.signal();
}
