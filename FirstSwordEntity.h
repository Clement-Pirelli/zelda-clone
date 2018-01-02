#pragma once
#include "SwordEntity.h"

class FirstSwordEntity : public SwordEntity{
public:
	FirstSwordEntity(PlayerAvatar* givenPlayer);
	~FirstSwordEntity();
	void update(float givenDeltaTime) override;
	void render() override;
	void onCollision(Entity* otherEntity) override;
	int getDamage() override;
private:
	const int damage = 1;
};

