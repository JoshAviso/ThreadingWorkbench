
#pragma once 

#include "IExecutionEvent.h"

class ThreadHandler : public IExecutionEvent {
public:
	bool isFinished = false;
	virtual void OnFinishedExecution() override {
		isFinished = true;
	};
};