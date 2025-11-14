
#pragma once

#include "IETThread.h"
#include "IExecutionEvent.h"

class MyThread : public IETThread {
public:
	bool isRunning = true;

	MyThread();
	~MyThread();
	void SetData(std::string _data) {
		data = _data;
	}
	void SetCallback(IExecutionEvent* callback) {
		onFinished = callback;
	}

private:
	std::string data = "default";
	IExecutionEvent* onFinished = nullptr;

	virtual void run() override;
};