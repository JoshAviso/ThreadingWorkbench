
#pragma once

#include "IWorkerAction.h"
#include "IETThread.h"

class IFinishedTask {
public:
	virtual void OnFinishedTask(int id) = 0;
};

class WorkerThread : public IETThread {
public:
	WorkerThread(int _id, IFinishedTask* _onFinish);
	~WorkerThread();

	void AssignTask(IWorkerAction* _task);
	int GetID() const { return this->id; }

private:
	void run() override;

	int id;
	IFinishedTask* onFinish;
	IWorkerAction* task;
};