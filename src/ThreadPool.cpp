#include "ThreadPool.h"

ThreadPool::ThreadPool(int _workerCount)
{
	workerCount = _workerCount;

	for (int i = 0; i < workerCount; i++) {
		InactiveThreads.push(new WorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::StartScheduling()
{
	this->isRunning = true;
	this->start();
}

void ThreadPool::StopScheduling()
{
	this->isRunning = false;
}

void ThreadPool::SecheduleTask(IWorkerAction* _task)
{
	this->PendingTasks.push(_task);
}

void ThreadPool::run()
{
	while (this->isRunning) {
		// Has task to do
		if (!this->PendingTasks.empty()) {
			// Has thread available
			if (!this->InactiveThreads.empty()) {
				// Take the queued inactive thread
				auto workerThread = this->InactiveThreads.front();
				this->InactiveThreads.pop();

				// Assign id in unordered map
				this->ActiveThreads[workerThread->GetID()] = workerThread;

				// Grab and assign queued task
				auto task = this->PendingTasks.front();
				this->PendingTasks.pop();
				workerThread->AssignTask(task);

				workerThread->start();
			}
		}
	}
}

void ThreadPool::OnFinishedTask(int id)
{
	if (this->ActiveThreads[id] != nullptr) {
		delete this->ActiveThreads[id];
		this->ActiveThreads.erase(id);

		InactiveThreads.push(new WorkerThread(id, this));
	}
}
