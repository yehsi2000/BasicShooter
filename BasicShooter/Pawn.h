#pragma once
#include "Actor.h"
class Pawn : public Actor
{
public:
	Pawn(class Game* game);
	void UpdateActor(float deltatime) override;
	virtual void ProcessInput(const uint8_t* state);
	Vector2 GetSpeed() const { return vSpeed; }
private:
	Vector2 vSpeed;
	int lastShootTick;;
	void Shoot();
};

