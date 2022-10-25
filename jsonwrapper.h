#ifndef _DABOARD_JSONWRAPPER_H_
#define _DABOARD_JSONWRAPPER_H_

#include "pch.h"
#include "config.h"

#define _VERIFY(x)                                  \
	do {                                            \
		if(!(x)) {                                  \
			SPDLOG_ERROR("_VERIFY(" #x ") failed"); \
		}                                           \
	} while(false)

using DataBase = nlohmann::json;
using Object   = DataBase::object_t;

class json_wrapper : public DataBase {
public:
	using DataBase::DataBase;
	json_wrapper* getFirst(const string_t& name);

	template<typename T>
	T& getFirst(const string_t& name) {
		auto ptr = getFirst(name);
		_VERIFY(ptr != nullptr);
		return ptr->get_ref<T&>();
	}
};

#undef _VERIFY

#endif // _DABOARD_JSONWRAPPER_H_
