#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"

int main()
{
	Engine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "RogueLite"));
	
	Engine::ResourceSystem::Instance()->LoadTexture("Ball", "Resourses/Textures/ball.png");
	Engine::ResourceSystem::Instance()->LoadSoundBuffer("Background", "Resourses/Sound/Clinthammer__Background_Music.wav");
	Engine::ResourceSystem::Instance()->LoadTextureMap("Walls", "Resourses/Textures/Wall.png", { 16, 16 }, 48, false);
	Engine::ResourceSystem::Instance()->LoadTextureMap("Floor", "Resourses/Textures/Floor.png", { 32, 32 }, 25, false);

	auto developerLevel = std::make_shared<RogueLite::DeveloperLevel>();
	developerLevel->Start();

	Engine::Engine::Instance()->Run();
	
	return 0;
}
