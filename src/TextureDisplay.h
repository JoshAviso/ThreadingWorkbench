#pragma once
#include <mutex>
#include "AGameObject.h"
#include "LoadAssetThread.h"
#include "ThreadPool.h"

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void OnFinishedExecution() override {
		this->spawnObject();
	}

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	ThreadPool threadPool = ThreadPool(50);

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 500.0f;
	const StreamingType streamingType = BATCH_LOAD;
	const int BATCH_SIZE = 20;
	float ticks = 100.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0; int texCount = 0;
	
	const int MAX_COLUMN = 14;
	const int MAX_ROW = 11;

	std::mutex guard;

	void spawnObject();
};

