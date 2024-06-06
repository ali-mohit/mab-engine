#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>


namespace MABEngine {
	namespace Debugging {

		using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

		struct MABENGINE_API ProfileResult {
			std::string Name;

			FloatingPointMicroseconds Start;
			std::chrono::microseconds ElapsedTime;
			std::thread::id ThreadID;
		};

		struct MABENGINE_API ProfileSession
		{
			std::string Name;
		};

		typedef MABENGINE_API std::function<void(ProfileResult)> ProfilerFunction;

		class MABENGINE_API Instrumentor
		{
		public:
			Instrumentor(const Instrumentor&) = delete;
			Instrumentor(Instrumentor&&) = delete;

			void BeginSession(const std::string& name, const std::string& filepath = "results.json")
			{
				std::lock_guard lock(m_Mutex);
				if (m_CurrentSession)
				{
					// If there is already a current session, then close it before beginning new one.
					// Subsequent profiling output meant for the original session will end up in the
					// newly opened session instead.  That's better than having badly formatted
					// profiling output.
					if (Logging::Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
					{
						MAB_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
					}
					InternalEndSession();
				}
				m_OutputStream.open(filepath);

				if (m_OutputStream.is_open())
				{
					m_CurrentSession = new ProfileSession({ name });
					WriteHeader();
				}
				else
				{
					if (Logging::Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
					{
						MAB_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
					}
				}
			}

			void EndSession()
			{
				std::lock_guard lock(m_Mutex);
				InternalEndSession();
			}

			void WriteProfile(const ProfileResult& result)
			{
				std::stringstream json;

				json << std::setprecision(3) << std::fixed;
				json << ",{";
				json << "\"cat\":\"function\",";
				json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
				json << "\"name\":\"" << result.Name << "\",";
				json << "\"ph\":\"X\",";
				json << "\"pid\":0,";
				json << "\"tid\":" << result.ThreadID << ",";
				json << "\"ts\":" << result.Start.count();
				json << "}";

				std::lock_guard lock(m_Mutex);
				if (m_CurrentSession)
				{
					m_OutputStream << json.str();
					m_OutputStream.flush();
				}
			}

			static Instrumentor& Get()
			{
				static Instrumentor instance;
				return instance;
			}
		private:
			Instrumentor()
				: m_CurrentSession(nullptr)
			{
			}

			~Instrumentor()
			{
				EndSession();
			}

			void WriteHeader()
			{
				m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
				m_OutputStream.flush();
			}

			void WriteFooter()
			{
				m_OutputStream << "]}";
				m_OutputStream.flush();
			}

			// Note: you must already own lock on m_Mutex before
			// calling InternalEndSession()
			void InternalEndSession()
			{
				if (m_CurrentSession)
				{
					WriteFooter();
					m_OutputStream.close();
					delete m_CurrentSession;
					m_CurrentSession = nullptr;
				}
			}
		private:
			std::mutex m_Mutex;
			ProfileSession* m_CurrentSession;
			std::ofstream m_OutputStream;
		};

		class MABENGINE_API InstrumentationTimer {
		public:
			InstrumentationTimer(const char* name, bool printInConsole=false)
				:m_Name(name), m_Func(nullptr), m_Stopped(false), m_PrintInConsole(printInConsole)
			{
				m_StartTimePoint = std::chrono::high_resolution_clock::now();
			}

			InstrumentationTimer(const char* name, const ProfilerFunction& fn)
				:m_Name(name), m_Func(fn), m_Stopped(false), m_PrintInConsole(false)
			{
				m_StartTimePoint = std::chrono::high_resolution_clock::now();
			}

			InstrumentationTimer(const char* name, const ProfilerFunction& fn, bool printInConsole)
				:m_Name(name), m_Func(fn), m_Stopped(false), m_PrintInConsole(printInConsole)
			{
				m_StartTimePoint = std::chrono::high_resolution_clock::now();
			}

			~InstrumentationTimer() {
				if (!m_Stopped)
					Stop();
			}

			void Stop() {
				auto endTimepoint = std::chrono::steady_clock::now();
				auto highResStart = FloatingPointMicroseconds{ m_StartTimePoint.time_since_epoch() };
				auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch();

				Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

				m_Stopped = false;

				if (m_PrintInConsole)
					std::cout << m_Name << ": " << elapsedTime.count() << "ms " << std::endl;

				if (m_Func != nullptr) {
					m_Func({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });
				}
			}
		private:
			const char* m_Name;
			ProfilerFunction m_Func;
			bool m_Stopped = false;
			bool m_PrintInConsole;
			std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
		};

		template <size_t N>
		struct MABENGINE_API ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}
