#pragma once

class RenderManager;
class InputManager;
class SpriteManager;
class StateManager;
class SoundManager;

class Engine{
public:
	Engine();
	~Engine();
	void initialize();
	void shutdown();
	void run();
private:
	void handleEvents();
	void calculateDeltaTime();
	float deltaTime = 0.0f;
	bool running = true;
	unsigned int lastTickCount = 0;
	RenderManager* myRenderManager = nullptr;
	InputManager* myInputManager = nullptr;
	SpriteManager* mySpriteManager = nullptr;
	StateManager* myStateManager = nullptr;
	SoundManager* mySoundManager = nullptr;
};

