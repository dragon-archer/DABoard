// Config file
// Not defined in pch.h to reduce compile time
#ifndef _DABOARD_CONFIG_H_
#define _DABOARD_CONFIG_H_

#include "pch.h"

#define DEFAULT_DATAFILE "data/default.da"
#define DEFAULT_TABSIZE 4
#ifndef NDEBUG
	#define DEFAULT_LOG_LEVEL	::spdlog::level::trace
	#define DEFAULT_LOG_PATTERN "[%H:%M:%S.%e](%s:%#) %^[%l]%$ %v"
#else
	#define DEFAULT_LOG_LEVEL	::spdlog::level::warn
	#define DEFAULT_LOG_PATTERN "[%Y-%m-%d %H:%M:%S.%e] %^[%l]%$ %v"
#endif

#define _TO_STRING_HELPER(x) #x
#define _TO_STRING(x)		 _TO_STRING_HELPER(x)

using namespace std::literals;

#endif // _DABOARD_CONFIG_H_
