#pragma once
#include "SwordItem.h"

class FirstSwordEntity;

class FirstSwordItem : public SwordItem{
public:
	FirstSwordItem();
	~FirstSwordItem();
	void use(PlayerAvatar* givenPlayer) override;
	void stopUse() override;
	void useFullHealth() override;
private:
	bool active = false;
	FirstSwordEntity* mySwordEntity = nullptr;
};

