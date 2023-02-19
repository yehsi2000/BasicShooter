#include "Game.h"
#include "SDL_image.h"
#include "Actor.h"
#include "Pawn.h"
#include "SpriteComponent.h"
#include <iostream>

Game::Game() :mWindow(nullptr), mRenderer(nullptr), bIsRunning(true), bUpdatingActor(false)
{
}

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Init Error\n%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Basic Shooter", 100, 100, 900, 600, 0);
	if (!mWindow) {
		SDL_Log("Init Error\n%s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Init Error\n%s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("SDL Image Init Error\n%s", SDL_GetError());
		return false;
	}

	Load();

	tickCount = SDL_GetTicks();

    return true;
}

void Game::Quit()
{
	Unload();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::Loop()
{
	while (bIsRunning) {
		Process_input();
		UpdateGame();
		Output();
	}
}

void Game::AddActor(Actor* actor)
{
	if (bUpdatingActor)
		vPendingActors.push_back(actor);
	else
		vActors.push_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(vPendingActors.begin(), vPendingActors.end(), actor);
	if (iter != vPendingActors.end()) {
		std::iter_swap(iter, vPendingActors.end() - 1);
		vPendingActors.pop_back();
	}
	iter = std::find(vActors.begin(), vActors.end(), actor);
	if (iter != vActors.end()) {
		std::iter_swap(iter, vActors.end() - 1);
		vActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int order = sprite->GetDrawOrder();
	auto iter = vSprites.begin();
	for (; iter != vSprites.end(); ++iter) {
		if (order < (*iter)->GetDrawOrder())
			break;
	}
	vSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(vSprites.begin(), vSprites.end(), sprite);
	vSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* texture = nullptr;
	auto iter = umTextures.find(filename);
	if (iter != umTextures.end()) {
		texture = iter->second;
	}
	else {
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface) {
			SDL_Log("Failed to load texture file %s", filename.c_str());
			return nullptr;
		}
		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);
		if (!texture) {
			SDL_Log("Failed to create texture from surface with file %s", filename.c_str());
			return nullptr;
		}

		umTextures.emplace(filename.c_str(), texture);
	}
    return texture;
}

void Game::Process_input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			bIsRunning = false;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		bIsRunning = false;
	}
	APlayer->ProcessInput(state);
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), tickCount + 16));

	float deltaTime = (SDL_GetTicks() - tickCount) / 1000.0f;
	if (deltaTime > 0.04f) {
		deltaTime = 0.04f;
	}
	tickCount = SDL_GetTicks();
	bUpdatingActor = true;
	for (auto actor : vActors) 
		actor->Update(deltaTime);
	bUpdatingActor = false;

	for (auto pending : vPendingActors)
	{
		vActors.push_back(pending);
	}
	vPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : vActors){
		if (actor->GetState() == Actor::EDead)
			deadActors.push_back(actor);
	}

	for (auto actor : deadActors)
		delete actor;
}

void Game::Output()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	for (auto sprite : vSprites)
		sprite->Draw(mRenderer);

	SDL_RenderPresent(mRenderer);
}

void Game::Load()
{
	APlayer = new Pawn(this);
	APlayer->SetPosition(Vector2(100.0f, 384.0f));
	APlayer->SetScale(1.5f);
}

void Game::Unload()
{
	while (!vActors.empty())
	{
		delete vActors.back();
	}

	// Destroy textures
	for (auto i : umTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	umTextures.clear();
}
