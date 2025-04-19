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
	private:
		std::string message;
	};

	class BadResource : public Exception
	{
	public:
		BadResource(const char* msg)
			: Exception(msg)
		{

		}

	};
}
