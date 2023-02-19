#pragma once
#include <vector>
#include "Math.h"

//typedef std::vector<float, float> Vector2;

class Actor {
public:
	enum State{EActive, EPaused, EDead};
	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	const Vector2& GetPosition() const { return Position; }
	void SetPosition(const Vector2& pos) { Position = pos; }
	float GetScale() const { return fScale; }
	void SetScale(const float scale) { fScale = scale; }
	float GetRotation() const { return fRotation; }
	void SetRotation(const float rotation) { fRotation = rotation; }

	State GetState() const { return eState; }
	void SetState(const State state) { eState = state; }

	class Game* GetGame() { return mGame; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	class Game* mGame;
	std::vector<class Component*> vComponents;
	State eState;

	Vector2 Position;
	float fScale;
	float fRotation;

	
};

