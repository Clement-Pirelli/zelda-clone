#pragma once
class Keyboard{
public:
	Keyboard();
	~Keyboard();
	bool isKeyPressed(SDL_Scancode givenKey);
	bool isKeyDown(SDL_Scancode givenKey);
	bool isKeyReleased(SDL_Scancode givenKey);
	void lateUpdate(float givenDeltaTime);
	void handleEvents(SDL_Event &givenEvent);
private:
	void setKey(SDL_Scancode givenKey, bool keyValue);
	bool keys[SDL_NUM_SCANCODES];
	bool keysLastFrame[SDL_NUM_SCANCODES];
};

