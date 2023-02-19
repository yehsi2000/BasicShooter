#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int draworder): SpriteComponent(owner,draworder), fCurrFrame(0.0f), fAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	size_t animsize = vAnimTextures.size();
	if (animsize > 0) {
		fCurrFrame += fAnimFPS * deltaTime;
		while (fCurrFrame >= animsize) fCurrFrame -= animsize;
		SetTexture(vAnimTextures[static_cast<int>(fCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	vAnimTextures = textures;
	if (vAnimTextures.size() > 0) {
		fCurrFrame = 0.0f;
		SetTexture(vAnimTextures[0]);
	}
}
