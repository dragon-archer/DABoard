#include "config.h"
#include "pch.h"
#include "jsonwrapper.h"

#define _VERIFY(x)                                  \
	do {                                            \
		if(!(x)) {                                  \
			SPDLOG_ERROR("_VERIFY(" #x ") failed"); \
		}                                           \
	} while(false)

json_wrapper* json_wrapper::getFirst(const string_t& name) {
	_VERIFY(is_object());
	auto& x		 = this->get_ref<object_t&>();
	auto& [k, v] = *x.lower_bound(name + DEFAULT_SEPERATOR);
	if(k.starts_with(name)) {
		return static_cast<json_wrapper*>(&v[1]);
	}
	return nullptr;
}

#undef _VERIFY
