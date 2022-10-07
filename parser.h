#ifndef _DABOARD_PARSER_H_
#define _DABOARD_PARSER_H_

#include "pch.h"
#include "config.h"

namespace da {
	using Data		 = nlohmann::json;
	using String	 = std::string;
	using StringView = std::string_view;
	using Char		 = char;
	using Number	 = int64_t;
	template<typename K, typename V>
	using Map = std::unordered_map<K, V>;

	enum class DataType {
		Error,
		Bool,
		Number,
		String,
		Array,
		Compound,
	};

	enum class DataOrder {
		Type,
		Name,
		Value,
	};

	enum class TokenType {
		Error,
		White,
		Comment,
		Operator,
		Number,
		String,
		Keyword,
		Identifier,
	};

	enum class Operator {
		Error,
		Equal,
		LeftBrace,
		RightBrace,
	};

	inline static const Map<Char, Operator> OperatorList {
		{ '=', Operator::Equal },
		{ '{', Operator::LeftBrace },
		{ '}', Operator::RightBrace },
	};

	enum class Keyword {
		Error,
		True,
		False,
	};

	inline static const Map<StringView, Keyword> KeywordList {
		{ "true"sv, Keyword::True },
		{ "false"sv, Keyword::False },
	};

	struct Location {
		// As `cur` is the most frequently used, put it at first
		StringView::iterator cur;
		int					 row = 1;
		int					 col = 1;
		StringView			 filename;

		inline Location(StringView::iterator iter, StringView f = ""sv)
			: cur(iter)
			, filename(f) {
		}

#define _TRACE(location, ...) SPDLOG_TRACE("{}:{}:{}: {}", location.filename, location.row, location.col, __VA_ARGS__)
#define _ERROR(location, ...) SPDLOG_ERROR("{}:{}:{}: {}", location.filename, location.row, location.col, __VA_ARGS__)
	};

	class Parser {
	public:
		inline Parser(StringView s, StringView filename = ""sv)
			: _content(s)
			, _current(s.begin(), filename) { }

		inline bool parse(Data& result) {
			return parseCompound(result, true);
		}

	private:
		StringView _content;
		Location   _current;
		bool	   _error = false;

		bool parseCompound(Data& result, bool ignoreBracket);
		bool parseStatement(Data& result);

		inline bool parseEnd() noexcept {
			return _current.cur == _content.end()
				|| (*_current.cur == '\0');
		}

		TokenType peekNextToken() noexcept;

		bool	   nextWhite() noexcept;
		bool	   nextComment() noexcept;
		Operator   nextOperator() noexcept;
		Number	   nextNumber() noexcept;
		StringView nextString() noexcept;
		StringView nextIdentifier() noexcept;

		bool skipWhite() noexcept;
	};
}

#endif // _DABOARD_PARSER_H_
