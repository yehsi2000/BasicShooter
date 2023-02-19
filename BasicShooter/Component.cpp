#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)	:mOwner(owner), iUpdateOrder(updateOrder) {
	mOwner->AddComponent(this);
}

Component::~Component() {
	mOwner->RemoveComponent(this);
}
