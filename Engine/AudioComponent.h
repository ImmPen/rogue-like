#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>

namespace Engine
{
    class ENGINE_API AudioComponent :
        public Component
    {
    public:
        AudioComponent(GameObject* gameObject);
        ~AudioComponent();

        void Update(float deltaTime) override;
        void Render() override;

        void SetAudio(const sf::SoundBuffer& buffer);
        void SetLoop(bool loop);

        void Play();
        void Pause();
        void Stop();
        void Resume();
        void SetVolume(float volume);
    private:
        sf::Sound* sound;
    };
}
