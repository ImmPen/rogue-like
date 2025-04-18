#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <memory>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine
{
	enum class LogLevel
	{
		T_INFO,
		T_WARNING,
		T_ERROR
	};

	class ENGINE_API LogSink
	{
	public:
		virtual void Log(LogLevel level, std::string message) = 0;
		virtual ~LogSink() = default;
	protected:
		static std::string LogLevelToString(LogLevel level)
		{
			switch (level)
			{
			case LogLevel::T_INFO:
				return "[INFO]: ";
				break;
			case LogLevel::T_WARNING:
				return "[WARNING]: ";
				break;
			case LogLevel::T_ERROR:
				return "[ERROR]: ";
				break;
			default:
				return "[UNKNOWN]: ";
				break;
			}
		}
	};

	class ENGINE_API ConsoleSink : public LogSink
	{
		void Log(LogLevel level, std::string message) override
		{
			std::cout << LogLevelToString(level) << message << std::endl;
		}
	};

	class ENGINE_API FileSink : public LogSink
	{
	public:
		FileSink(std::string filePath)
		{
			file.open(filePath, std::ios::app);
			if (!file.is_open())
			{
				std::cout << "What?" << std::endl;
			}
		}
		~FileSink()
		{
			file.close();
		}

		void Log(LogLevel level, std::string message) override
		{
			file << LogLevelToString(level) << message << std::endl;
		}
	private:
		std::fstream file;
	};

	class ENGINE_API Logger
	{
	public:
		void AddSink(std::shared_ptr<LogSink> sink)
		{
			sinks.push_back(sink);
		}
		void Log(LogLevel level, std::string message)
		{
			std::lock_guard<std::mutex> lock(logMutex);
			for (auto sink : sinks)
			{
				sink->Log(level, message);
			}
		}

		void Info(std::string message) { Log(LogLevel::T_INFO, message); }
		void Warn(std::string message) { Log(LogLevel::T_WARNING, message); }
		void Error(std::string message) { Log(LogLevel::T_ERROR, message); }
	private:
		std::mutex logMutex;
		std::vector<std::shared_ptr<LogSink>> sinks;
	};

	class ENGINE_API LoggerRegistry
	{
	public:
		void SetDefaultLogger(std::shared_ptr<Logger> logger)
		{
			defaultLogger = logger;
		}

		static LoggerRegistry& GetInstance()
		{
			static LoggerRegistry instance;
			return instance;
		}

		std::shared_ptr<Logger> GetLogger(std::string name)
		{
			std::lock_guard<std::mutex> lock(registryMutex);
			if (loggers.find(name) != loggers.end())
			{
				return loggers[name];
			}

			return defaultLogger;
		}

		void RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger)
		{
			std::lock_guard<std::mutex> lock(registryMutex);
			loggers[name] = logger;
		}
	private:
		std::shared_ptr<Logger> defaultLogger;
		std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
		std::mutex registryMutex;
	};
}

#define LOG_INFO(message) Engine::LoggerRegistry::GetInstance().GetLogger("global")->Info(message)
#define LOG_WARN(message) Engine::LoggerRegistry::GetInstance().GetLogger("global")->Warn(message)
#define LOG_ERROR(message) Engine::LoggerRegistry::GetInstance().GetLogger("global")->Error(message)
