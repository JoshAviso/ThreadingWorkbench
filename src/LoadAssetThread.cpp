#include "LoadAssetThread.h"

LoadAssetThread::LoadAssetThread()
{
}

LoadAssetThread::~LoadAssetThread()
{
}

LoadAssetThread::LoadAssetThread(int _id, IExecutionEvent* callback) { id = _id; onFinish = callback; }

void LoadAssetThread::OnStartTask()
{
	TextureManager::getInstance()->loadSingleStreamAsset(id);
	onFinish->OnFinishedExecution();

	delete this;
}
