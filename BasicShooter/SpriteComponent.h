#pragma once
#include "Component.h"
#include "SDL.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int draworder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return iDrawOrder; }
	int GetTextureHeight() const { return iTexHeight; }
	int GetTextureWidth() const { return iTexWidth; }
protected:
	SDL_Texture* mTexture;
	int iDrawOrder;
	int iTexHeight;
	int iTexWidth;
};

