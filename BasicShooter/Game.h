#pragma once
#include "SDL.h"
#include <string>
#include <unordered_map>
#include <vector>

class Game {
public:
	Game();
	bool Init();
	void Quit();
	void Loop();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	SDL_Texture* GetTexture(const std::string& fileName);
private:
	void Process_input();
	void UpdateGame();
	void Output();
	void Load();
	void Unload();

	std::unordered_map<std::string, SDL_Texture*> umTextures;
	std::vector<class SpriteComponent*> vSprites;
	std::vector<class Actor*> vActors;
	std::vector<class Actor*> vPendingActors;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 tickCount;
	bool bIsRunning;
	bool bUpdatingActor;
	class Pawn* APlayer;

};