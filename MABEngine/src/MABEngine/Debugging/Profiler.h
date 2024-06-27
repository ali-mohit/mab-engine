#pragma once

#include "MABEngine/Debugging/Instrumentor.h"


#define MAB_PROFILE 1
#if MAB_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define MAB_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define MAB_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define MAB_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define MAB_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define MAB_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define MAB_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define MAB_FUNC_SIG __func__
#else
#define MAB_FUNC_SIG "MAB_FUNC_SIG unknown!"
#endif

#define MAB_PROFILE_BEGIN_SESSION(name, filepath) ::MABEngine::Debugging::Instrumentor::Get().BeginSession(name, filepath)
#define MAB_PROFILE_END_SESSION() ::MABEngine::Debugging::Instrumentor::Get().EndSession()
#define MAB_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::MABEngine::Debugging::CleanupOutputString(name, "__cdecl ");\
											   ::MABEngine::Debugging::InstrumentationTimer timer##line(fixedName##line.Data)
#define MAB_PROFILE_SCOPE_LINE(name, line) MAB_PROFILE_SCOPE_LINE2(name, line)
#define MAB_PROFILE_SCOPE(name) MAB_PROFILE_SCOPE_LINE(name, __LINE__)
#define MAB_PROFILE_FUNCTION() MAB_PROFILE_SCOPE(MAB_FUNC_SIG)
#else
#define MAB_PROFILE_BEGIN_SESSION(name, filepath)
#define MAB_PROFILE_END_SESSION()
#define MAB_PROFILE_SCOPE(name)
#define MAB_PROFILE_FUNCTION()
#endif