#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game):eState(EActive), Position(Vector2 {0,0}), fScale(1.0f), fRotation(0.0f), mGame(game) {
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (!vComponents.empty()) {
		delete vComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (eState == EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto component : vComponents) {
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::AddComponent(Component* component) 
{
	int upOrder = component->GetUpdateOrder();
	auto iter = vComponents.begin();
	for (; iter != vComponents.end(); ++iter) {
		if (upOrder < (*iter)->GetUpdateOrder())
			break;
	}
	vComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(vComponents.begin(), vComponents.end(), component);
	if (iter != vComponents.end()) {
		vComponents.erase(iter);
	}
}
