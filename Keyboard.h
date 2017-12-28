#pragma once
class Keyboard{
public:
	Keyboard();
	~Keyboard();
	bool isKeyPressed(SDL_Scancode givenkey);
	bool isKeyDown(SDL_Scancode givenkey);
	bool isKeyReleased(SDL_Scancode givenkey);
	void lateUpdate(float deltatime);
	void handleEvents(SDL_Event &givenevent);
private:
	void setKey(SDL_Scancode givenkey, bool keyvalue);
	bool keys[SDL_NUM_SCANCODES];
	bool keysLastFrame[SDL_NUM_SCANCODES];
};

