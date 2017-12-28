#pragma once

enum COLLIDERTYPE {
	RECTANGLE,
	NOT_SET
};

class Collider{
public:
	Collider(){};
	virtual ~Collider(){};
	virtual COLLIDERTYPE getType() = 0;
};