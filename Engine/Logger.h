#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <memory>

namespace Engine
{
	enum class LogLevel
	{
		T_INFO,
		T_WARNING,
		T_ERROR
	};

	class LogSink
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

	class ConsoleSink : public LogSink
	{
		void Log(LogLevel level, std::string message) override
		{
			std::cout << LogLevelToString(level) << message << std::endl;
		}
	};

	class FileSink : public LogSink
	{
	public:
		FileSink(std::string filePath)
		{
			file.open(filePath, std::ios::app);
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

	class Logger
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

	class LoggerRegistry
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
	private:
		std::shared_ptr<Logger> defaultLogger;
		std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
		std::mutex registryMutex;
	};

#define LOG_INFO(message) LoggerRegistry::GetInstance().GetLogger("global")->Info(message)
#define LOG_WARN(message) LoggerRegistry::GetInstance().GetLogger("global")->Warn(message)
#define LOG_ERROR(message) LoggerRegistry::GetInstance().GetLogger("global")->Error(message)
}