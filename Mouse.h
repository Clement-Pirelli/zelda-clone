#pragma once
class Mouse
{
	static const int MAXBUTTONS = 5;
public:
	Mouse();
	~Mouse();
	bool isMouseButtonDown(int givenButton);
	bool isMouseButtonPressed(int givenButton);
	bool isMouseButtonReleased(int givenButton);
	SDL_Point getMousePosition();
	SDL_Point getMouseMotion();
	void handleEvents(SDL_Event &givenEvent);
	void lateUpdate(float givenDeltaTime);
private:
	void setButton(int buttonIndex, bool givenValue);
	SDL_Point position;
	SDL_Point motion;
	bool buttons[MAXBUTTONS];
	bool buttonsLastFrame[MAXBUTTONS];
};