#pragma once
#include "InventoryItem.h"

class SwordItem : public InventoryItem{
public:
	SwordItem() {};
	virtual ~SwordItem() {};
	virtual void useFullHealth() = 0;
	virtual void stopUse() = 0;
};