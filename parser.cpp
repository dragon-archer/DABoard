#include "pch.h"
#include "parser.h"

namespace da {
	bool Parser::parse(Data &result) {
		result.clear();
		auto cur = _content.begin();
		result = Data::parse(_content.begin(), _content.end(), nullptr, false, true);
		return true;
	}
}
