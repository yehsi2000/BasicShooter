#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int draworder) : Component(owner), mTexture(nullptr), iDrawOrder(draworder), iTexHeight(0), iTexWidth(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture) {
		SDL_Rect rect;
		rect.w = static_cast<int>(iTexWidth * mOwner->GetScale());
		rect.h = static_cast<int>(iTexHeight * mOwner->GetScale());
		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &rect, -mOwner->GetRotation(), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &iTexWidth, &iTexHeight);
}
