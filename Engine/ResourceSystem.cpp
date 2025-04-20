#include "pch.h"
#include "ResourceSystem.h"

namespace Engine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem system;
		return &system;
	}

	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.find(name) != textures.end())
		{
			return;
		}
		sf::Texture* newTexture = new sf::Texture;
		if (newTexture->loadFromFile(sourcePath))
		{
			newTexture->setSmooth(isSmooth);
			textures.emplace(name, newTexture);
		}
		else
		{
			LOG_ERROR("Texture not found: " + sourcePath);
			throw TextureNotFound(sourcePath.c_str());
		}
	}

	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		return textures.find(name)->second;
	}

	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		return new sf::Texture(*textures.find(name)->second);
	}

	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		auto texturePair = textures.find(name);

		sf::Texture* deletingTexture = texturePair->second;
		textures.erase(texturePair);
		delete deletingTexture;
	}

	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		if (textureMaps.find(name) != textureMaps.end())
		{
			return;
		}

		sf::Texture textureMap;
		if (textureMap.loadFromFile(sourcePath))
		{
			auto textureMapElements = new std::vector<sf::Texture*>();

			auto textureSize = textureMap.getSize();
			int loadedElements = 0;

			for (unsigned int y = 0; y <= textureSize.y - elementPixelSize.y; y += elementPixelSize.y)
			{
				if (loadedElements == totalElements)
				{
					break;
				}

				for (unsigned int x = 0; x <= textureSize.x - elementPixelSize.x; x += elementPixelSize.x)
				{
					if (loadedElements == totalElements)
					{
						break;
					}

					sf::Texture* newTextureMapElement = new sf::Texture();
					if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						newTextureMapElement->setSmooth(isSmooth);
						textureMapElements->push_back(newTextureMapElement);
					}
					loadedElements++;
				}
			}
			textureMaps.emplace(name, *textureMapElements);
		}
		else
		{
			LOG_ERROR("Texture map not found: " + sourcePath);
			throw TextureMapNotFound(sourcePath.c_str());
		}
	}

	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures[elementIndex];
	}

	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return new sf::Texture(*textures[elementIndex]);
	}

	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return (int)textures.size();
	}

	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);
		auto deletingTextures = textureMap->second;

		for (auto& toDelete : deletingTextures)
		{
			delete toDelete;
		}

		textureMaps.erase(textureMap);
	}

	void ResourceSystem::LoadSoundBuffer(const std::string& name, std::string sourcePath)
	{
		if (soundBuffers.find(name) != soundBuffers.end())
		{
			return;
		}
		sf::SoundBuffer* newBuffer = new sf::SoundBuffer;
		if (newBuffer->loadFromFile(sourcePath))
		{
			soundBuffers.emplace(name, newBuffer);
		}
		else
		{
			LOG_ERROR("Sound buffer not found: " + sourcePath);
			throw SoundBufferNotFound(sourcePath.c_str());
		}
	}

	const sf::SoundBuffer* ResourceSystem::GetSoundBuffer(const std::string& name) const
	{
		return soundBuffers.find(name)->second;
	}

	void ResourceSystem::DeleteSharedSoundBuffer(const std::string& name)
	{
		auto bufferPair = soundBuffers.find(name);

		sf::SoundBuffer* deletingBuffer = bufferPair->second;
		soundBuffers.erase(bufferPair);
		delete deletingBuffer;
	}

	void ResourceSystem::Clear()
	{
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllSoundBuffers();
	}

	void ResourceSystem::DeleteAllTextures()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& texturePair : textures)
		{
			keysToDelete.push_back(texturePair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTexture(key);
		}
	}

	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}

	void ResourceSystem::DeleteAllSoundBuffers()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& soundBufferPair : textureMaps)
		{
			keysToDelete.push_back(soundBufferPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedSoundBuffer(key);
		}
	}
}
