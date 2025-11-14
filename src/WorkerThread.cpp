#include "WorkerThread.h"

WorkerThread::WorkerThread(int _id, IFinishedTask* _onFinish) : id(_id), onFinish(_onFinish), task(nullptr) {}

WorkerThread::~WorkerThread() {}

void WorkerThread::AssignTask(IWorkerAction* _task)
{
	this->task = _task;
}

void WorkerThread::run()
{
	if (task != nullptr) task->OnStartTask();

	if (onFinish != nullptr) onFinish->OnFinishedTask(this->id);
}
