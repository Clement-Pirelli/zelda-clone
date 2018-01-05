#include "stdafx.h"
#include "PlayerVariablesUI.h"
#include "Service.h"
#include "RenderManager.h"

PlayerVariablesUI::PlayerVariablesUI(PlayerAvatar* givenPlayer){
	myPlayer = givenPlayer;
	myRenderManager = Service<RenderManager>::getService();
}

PlayerVariablesUI::~PlayerVariablesUI(){
	myRenderManager = nullptr;
	myPlayer = nullptr;
}

void PlayerVariablesUI::render(){
}
