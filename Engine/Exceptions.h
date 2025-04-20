#pragma once

#include <exception>
#include <string>

namespace Engine
{
	class Exception : public std::exception
	{
	public:
		Exception(const char* msg)
			: message(msg)
		{

		}
		virtual const char* what() const override
		{
			return message.c_str();
		}
		virtual ~Exception() = default;
	protected:
		std::string message;
	};

	class ResourceNotFound : public Exception
	{
	public:
		ResourceNotFound(const char* msg)
			: Exception(msg)
		{

		}
	};
	
	class TextureNotFound : public ResourceNotFound
	{
	public:
		TextureNotFound(const char* msg)
			: ResourceNotFound(msg)
		{

		}
	};

	class TextureMapNotFound : public ResourceNotFound
	{
	public:
		TextureMapNotFound(const char* msg)
			: ResourceNotFound(msg)
		{

		}
	};
	
	class SoundBufferNotFound : public ResourceNotFound
	{
	public:
		SoundBufferNotFound(const char* msg)
			: ResourceNotFound(msg)
		{

		}
	};
}
