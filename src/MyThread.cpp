#include "MyThread.h"

MyThread::MyThread()
{
}

MyThread::~MyThread()
{
}

void MyThread::run()
{
	std::cout << "Printing data: " << data << std::endl;

	isRunning = false;

	if(onFinished != nullptr) 
		this->onFinished->OnFinishedExecution();
	delete this;
}
