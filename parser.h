#ifndef _DABOARD_PARSER_H_
#define _DABOARD_PARSER_H_

#include "pch.h"
#include "config.h"

namespace da {
	using Data		 = nlohmann::json;
	using String	 = std::string;
	using StringView = std::string_view;

	enum class DataType {
		Error,
		Bool,
		Number,
		String,
		Array,
		Compound,
	};

	struct Location {
		int		   row;
		int		   col;
		StringView filename;

		inline void log(spdlog::level::level_enum lvl, StringView msg) const {
			spdlog::log(lvl, "{}:{}:{}: {}", filename, row, col, msg);
		}
	};

	class Parser {
	public:
		Parser(StringView s, Location loc = {})
			: _content(s)
			, _location(loc) { }

		bool parse(Data& result);

	private:
		StringView _content;
		Location   _location;
	};
}

#endif // _DABOARD_PARSER_H_
