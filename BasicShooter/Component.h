#pragma once
class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime) = 0;

	int GetUpdateOrder() const { return iUpdateOrder; }
protected:
	class Actor* mOwner;
	int iUpdateOrder;
};

