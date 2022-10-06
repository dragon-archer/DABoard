#include "pch.h"
#include "datastore.h"

namespace da {
	bool DataStore::readData(std::filesystem::path filename) {
		QFile file(filename);
		file.open(QFile::ReadOnly);
		size_t n = file.size();
		String s(n + 1, '\0');
		file.read(s.data(), n);
		Parser p(s);
		bool ret = p.parse(_data);
		file.close();
		return ret;
	}
}
