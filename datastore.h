#ifndef _DABOARD_DATASTORE_H_
#define _DABOARD_DATASTORE_H_

#include "pch.h"
#include "config.h"
#include "parser.h"

#define GLOBAL_DATA ::DataStore::getInstance().data()

// Note: Singleton
class DataStore {
public:
	inline static DataStore& getInstance() {
		static DataStore _instance;
		return _instance;
	}

private:
	DataStore()							  = default;
	~DataStore()						  = default;
	DataStore(const DataStore&)			  = delete;
	DataStore(DataStore&&)				  = delete;
	DataStore operator=(const DataStore&) = delete;
	DataStore operator=(DataStore&&)	  = delete;

public:
	bool readData(StringView filename);

	inline constexpr Data& data() {
		return _data;
	}

private:
	Data _data;
};

#endif // _DABOARD_DATASTORE_H_
