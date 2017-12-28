#pragma once
class Keyboard;
class InputManager
{
public:
	InputManager();
	~InputManager();
	bool initialize();
	void shutdown();
	bool isKeyPressed(SDL_Scancode givenKey);
	bool isKeyDown(SDL_Scancode givenKey);
	bool isKeyReleased(SDL_Scancode givenKey);
	void handleEvents(SDL_Event &givenEvent);
	void lateUpdate(float deltaTime);
private:
	Keyboard* myKeyboard = nullptr;
};

