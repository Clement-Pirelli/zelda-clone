#pragma once

class PlayerAvatar;
class RenderManager;
class Sprite;

class PlayerVariablesUI{
public:
	PlayerVariablesUI(PlayerAvatar* givenPlayer);
	~PlayerVariablesUI();
	void render();
private:
	RenderManager* myRenderManager = nullptr;
	PlayerAvatar* myPlayer = nullptr;
};

