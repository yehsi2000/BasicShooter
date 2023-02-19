#include "Pawn.h"
#include "Bullet.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Pawn::Pawn(Game* game) : Actor(game), vSpeed(Vector2(0.f,0.f))
{
	AnimSpriteComponent* animspritecomp = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> animtexture = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	animspritecomp->SetAnimTextures(animtexture);
}

void Pawn::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);
	Vector2 pos = GetPosition();
	pos.x += vSpeed.x * deltatime;
	pos.y += vSpeed.y * deltatime;
	if (pos.x < 25.0f) pos.x = 25.0f;
	else if (pos.x > 500.f) pos.x = 500.0f;
	
	if (pos.y < 25.0f) pos.y = 25.0f;
	else if (pos.y > 743.f) pos.y = 743.0f;

	SetPosition(pos);
}

void Pawn::ProcessInput(const uint8_t* state)
{
	vSpeed = Vector2(0.f,0.f);
	if (state[SDL_SCANCODE_D]) 	vSpeed.x += 200.0f;
	if (state[SDL_SCANCODE_A]) 	vSpeed.x -= 200.0f;
	if (state[SDL_SCANCODE_S]) 	vSpeed.y += 200.0f;
	if (state[SDL_SCANCODE_W]) 	vSpeed.y -= 200.0f;

	if (state[SDL_SCANCODE_J] && (SDL_GetTicks() - lastShootTick > 100)) Shoot();

}

void Pawn::Shoot()
{
	Bullet* bullet = new Bullet(this->GetGame());
	bullet->SetPosition(this->GetPosition()+Vector2(50.f,0));
	bullet->SetScale(2.0f);
	lastShootTick = SDL_GetTicks();
}
