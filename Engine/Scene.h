#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine
{
	class ENGINE_API Scene
	{
	public:
		virtual void Start() = 0;
		virtual void Restart() = 0;
		virtual void Stop() = 0;
	};
}