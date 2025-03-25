#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"


namespace RogueLite
{

	int main()
	{
		Engine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "RogueLite"));
		
		Engine::ResourceSystem::Instance()->LoadTexture("Ball", "Resources/Textures/ball.png");

		auto developerLevel = std::make_shared<DeveloperLevel>();
		developerLevel->Start();

		Engine::Engine::Instance()->Run();
		
		return 0;
	}
}
