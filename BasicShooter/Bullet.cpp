#include "Bullet.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Bullet::Bullet(Game* game) : Actor(game),fSpeed(400.0f)
{
	AnimSpriteComponent* animspritecomp = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> animtexture = {
		game->GetTexture("Assets/Bullet01.png"),
		game->GetTexture("Assets/Bullet02.png"),
		game->GetTexture("Assets/Bullet03.png"),
		game->GetTexture("Assets/Bullet04.png"),
	};
	//animspritecomp->SetAnimFPS(24.0f);
	animspritecomp->SetAnimTextures(animtexture);
	
}

void Bullet::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);
	Vector2 pos = GetPosition();
	pos.x += fSpeed * deltatime;
	SetPosition(pos);
	if (GetPosition().x > 1000.f) this->SetState(Actor::EDead);
}
