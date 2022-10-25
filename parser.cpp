#include "pch.h"
#include "parser.h"

#define _VERIFY(x)                                                         \
	do {                                                                   \
		if(!(x) || _error) {                                               \
			_ERROR(_current, "_VERIFY(" #x ") failed");                    \
			_ERROR(_current, StringView { _current.cur, _content.end() }); \
			_error = true;                                                 \
			return {};                                                     \
		}                                                                  \
	} while(false)

#define _CHECK()                                 \
	do {                                         \
		if(_error) {                             \
			_ERROR(_current, "_CHECK() failed"); \
			return {};                           \
		}                                        \
	} while(false)

static inline constexpr auto canStartIdentifier = [](Char ch) {
	return isalpha(ch) || ch == '_';
};
static inline constexpr auto canContinueIdentifier = [](Char ch) {
	return isalpha(ch) || isdigit(ch) || (ch == '_');
};
static inline constexpr auto canStartNumber = [](Char ch) {
	return isdigit(ch) || ch == '-';
};
static inline constexpr auto canContinueNumber = [](Char ch) {
	return isdigit(ch);
};

bool Parser::parseCompound(Data& result, bool ignoreBracket) {
	result.clear();
	_VERIFY(skipWhite());
	if(parseEnd()) {
		return ignoreBracket;
	}
	do {
		if(!ignoreBracket) {
			if(peekNextToken() == TokenType::Operator) {
				_VERIFY(nextOperator() == Operator::RightBrace);
				return true;
			}
		}
		_VERIFY(parseStatement(result));
		_VERIFY(skipWhite());
	} while(!parseEnd());
	return false;
}

bool Parser::parseStatement(Data& result) {
	_VERIFY(skipWhite());
	if(parseEnd()) {
		return true;
	}
	// Get LHS
	auto	   token = peekNextToken();
	StringView LHS;
	switch(token) {
	case TokenType::Identifier: // Only Identifier should appear before '='
		LHS = nextIdentifier();
		_VERIFY(!LHS.empty());
		break;
	default:
		_ERROR(_current, "Unexpected token"sv);
		return false;
	}
	_VERIFY(skipWhite());
	token = peekNextToken();
	_VERIFY(token == TokenType::Operator);
	_VERIFY(nextOperator() == Operator::Equal);
	_VERIFY(skipWhite());
	token	= peekNextToken();
	auto& x = result[formatName(LHS)];
	switch(token) {
	case TokenType::Number: {
		Int ret = nextNumber();
		_CHECK();
		x[0] = DataType::Number;
		x[1] = ret;
		return true;
	}
	case TokenType::String: {
		StringView ret = nextString();
		_CHECK();
		x[0] = DataType::String;
		x[1] = ret;
		return true;
	}
	case TokenType::Operator: {
		_VERIFY(nextOperator() == Operator::LeftBrace);
		x[0] = DataType::Compound;
		_VERIFY(parseCompound(static_cast<Data&>(x[1]), false));
		return true;
	}
	case TokenType::Keyword: {
		Keyword ret = nextKeyword();
		_VERIFY(ret != Keyword::Error);
		x[0] = DataType::Bool;
		x[1] = (ret == Keyword::True);
		return true;
	}
	default:
		_ERROR(_current, "Unexpected token"sv);
		return false;
	};
	return true;
}

TokenType Parser::peekNextToken() noexcept {
	Char ch = *_current.cur;
	if(isspace(ch)) {
		return TokenType::White;
	} else if(ch == '#') {
		return TokenType::Comment;
	} else if(OperatorList.contains(ch)) {
		return TokenType::Operator;
	} else if(canStartNumber(ch)) {
		return TokenType::Number;
	} else if(ch == '"') {
		return TokenType::String;
	} else if(canStartIdentifier(ch)) {
		auto it = _current.cur;
		do {
			++it;
			ch = *it;
		} while(!parseEnd() && canContinueIdentifier(ch));
		if(KeywordList.contains({ _current.cur, it })) {
			return TokenType::Keyword;
		}
		return TokenType::Identifier;
	}
	return TokenType::Error;
}

bool Parser::nextWhite() noexcept {
	Char ch = *_current.cur;
	if(!isspace(ch)) {
		return false;
	}
	while(!parseEnd()) {
		switch(ch) {
		case ' ':
			++_current.col;
			break;
		case '\t':
			_current.col += DEFAULT_TABSIZE;
			break;
		case '\n':
			_current.col = 0;
			++_current.row;
			break;
		case '\r':
		case '\v':
		case '\f':
			break; // Ignore them
		default:
			return true;
		}
		++_current.cur;
		ch = *_current.cur;
	}
	return true;
}

bool Parser::nextComment() noexcept {
	if(*_current.cur != '#') {
		_ERROR(_current, "Comment should start with '#'"sv);
		return false;
	}
	do {
		++_current.cur;
	} while(!parseEnd() && (*_current.cur != '\n'));
	++_current.cur; // Eat '\n'
	++_current.row;
	_current.col = 0;
	return true;
}

Operator Parser::nextOperator() noexcept {
	_VERIFY(!parseEnd());
	auto it = OperatorList.find(*_current.cur);
	_VERIFY(it != OperatorList.end());
	++_current.col;
	++_current.cur;
	return it->second;
}

// TODO: Add real number support
Int Parser::nextNumber() noexcept {
	_VERIFY(!parseEnd());
	auto beg = _current.cur;
	Char ch	 = *_current.cur;
	_VERIFY(canStartNumber(ch));
	Int ret		 = 0;
	Int negative = 1;
	if(ch == '-') {
		negative = -1;
		++_current.cur;
		ch = *_current.cur;
	}
	do {
		ret = ret * 10 + ch - '0';
		++_current.cur;
		ch = *_current.cur;
	} while(!parseEnd() && canContinueNumber(ch));
	_current.col += _current.cur - beg;
	return ret * negative;
}

StringView Parser::nextString() noexcept {
	_VERIFY(!parseEnd());
	auto beg = _current.cur;
	Char ch	 = *_current.cur;
	_VERIFY(ch == '"');
	bool backslash = false;
	do {
		++_current.cur;
		ch = *_current.cur;
		if(ch == '\\' || backslash) {
			backslash = !backslash;
		} else if(ch == '"') {
			break;
		}
	} while(!parseEnd());
	_VERIFY(!parseEnd());
	++_current.cur; // Eat '"'
	_current.col += _current.cur - beg;
	return { beg + 1, _current.cur - 1 }; // Eat '"'
}

Keyword Parser::nextKeyword() noexcept {
	StringView identifier = nextIdentifier();
	_CHECK();
	auto it = KeywordList.find(identifier);
	_VERIFY(it != KeywordList.end());
	return it->second;
}

StringView Parser::nextIdentifier() noexcept {
	_VERIFY(!parseEnd());
	auto beg = _current.cur;
	Char ch	 = *_current.cur;
	_VERIFY(canStartIdentifier(ch));
	do {
		++_current.cur;
		ch = *_current.cur;
	} while(!parseEnd() && canContinueIdentifier(ch));
	_current.col += _current.cur - beg;
	return { beg, _current.cur };
}

bool Parser::skipWhite() noexcept {
	while(!parseEnd()) {
		auto token = peekNextToken();
		switch(token) {
		case TokenType::White:
			_VERIFY(nextWhite());
			break;
		case TokenType::Comment:
			_VERIFY(nextComment());
			break;
		default:
			return true;
		}
	}
	return true;
}

#undef _VERIFY
#undef _CHECK
