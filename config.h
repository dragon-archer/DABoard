// Config file
// Not defined in pch.h to reduce compile time
#ifndef _DABOARD_CONFIG_H_
#define _DABOARD_CONFIG_H_

#include "pch.h"

// clang-format off
#define DEFAULT_DATAFILE  "data/default.da"
#define DEFAULT_TABSIZE   4
#define DEFAULT_SEPERATOR "#"
#ifndef NDEBUG
	#define DEFAULT_LOG_LEVEL	::spdlog::level::trace
	#define DEFAULT_LOG_PATTERN "[%H:%M:%S.%e](%s:%#) %^[%l]%$ %v"
#else
	#define DEFAULT_LOG_LEVEL	::spdlog::level::warn
	#define DEFAULT_LOG_PATTERN "[%Y-%m-%d %H:%M:%S.%e] %^[%l]%$ %v"
#endif

#define _TO_STRING_HELPER(x) #x
#define _TO_STRING(x)		 _TO_STRING_HELPER(x)
// clang-format on

using namespace std::literals;

using String	 = std::string;
using StringView = std::string_view;
using Char		 = char;
using Int		 = int64_t;
template<typename K, typename V>
using Map = std::unordered_map<K, V>;

enum class DataOrder {
	Type,
	Name,
	Value,
};

#endif // _DABOARD_CONFIG_H_
