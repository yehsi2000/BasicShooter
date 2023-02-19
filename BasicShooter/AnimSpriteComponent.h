#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int draworder = 100);
	void Update(float deltaTime) override;
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	float GetAnimFPS() const { return fAnimFPS; }
	void SetAnimFPS(float fps) { fAnimFPS = fps; }
private:
	std::vector<SDL_Texture*> vAnimTextures;
	float fCurrFrame;
	float fAnimFPS;
};

