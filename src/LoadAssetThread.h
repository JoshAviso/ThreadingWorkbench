
#pragma once

#include <iostream>
#include "IWorkerAction.h"
#include "IExecutionEvent.h"
#include "TextureManager.h"

class LoadAssetThread : public IWorkerAction {
public:
	LoadAssetThread();
	~LoadAssetThread();

	LoadAssetThread(int _id, IExecutionEvent* callback);

private:
	int id = 0;
	IExecutionEvent* onFinish;

	void OnStartTask() override;

};