#include "pch.h"
#include "AudioComponent.h"

namespace Engine
{
	AudioComponent::AudioComponent(GameObject* gameObject)
		: Component(gameObject)
	{
		sound = new sf::Sound;
	}

	AudioComponent::~AudioComponent()
	{
		Stop();
		delete sound;
	}

	void AudioComponent::Update(float deltaTime)
	{
	}

	void AudioComponent::Render()
	{
	}

	void AudioComponent::SetAudio(const sf::SoundBuffer& buffer)
	{
		sound->setBuffer(buffer);
	}

	void AudioComponent::SetLoop(bool loop)
	{
		sound->setLoop(loop);
	}

	void AudioComponent::Play()
	{
		if (sound->getStatus() != sf::SoundSource::Playing)
		{
			sound->play();
		}
	}

	void AudioComponent::Pause()
	{ 
		sound->pause();
	}

	void AudioComponent::Stop()
	{
		sound->stop();
	}

	void AudioComponent::Resume()
	{
		if (sound->getStatus() != sf::SoundSource::Playing)
		{
			sound->play();
		}
	}

	void AudioComponent::SetVolume(float volume)
	{
		sound->setVolume(volume);
	}


}