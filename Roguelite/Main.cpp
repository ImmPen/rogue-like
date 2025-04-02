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

	auto developerLevel = std::make_shared<RogueLite::DeveloperLevel>();
	developerLevel->Start();

	Engine::Engine::Instance()->Run();
	
	return 0;
}
