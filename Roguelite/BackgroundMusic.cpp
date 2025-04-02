#include "BackgroundMusic.h"


namespace RogueLite
{
	BackgroundMusic::BackgroundMusic()
	{
		gameObject = Engine::GameWorld::Instance()->CreateGameObject();

		auto musicAudioComponent = gameObject->AddComponent<Engine::AudioComponent>();
		musicAudioComponent->SetAudio(*Engine::ResourceSystem::Instance()->GetSoundBuffer("Background"));
		musicAudioComponent->SetLoop(true);
		musicAudioComponent->SetVolume(50.f);
		musicAudioComponent->Play();
	}

	Engine::GameObject* BackgroundMusic::GetGameObject()
	{
		return gameObject;
	}
}
