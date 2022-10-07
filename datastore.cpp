#include "pch.h"
#include "datastore.h"

namespace da {
	bool DataStore::readData(StringView filename) {
		QFile file(QString::fromUtf8(filename.data(), filename.size()));
		file.open(QFile::ReadOnly);
		size_t n = file.size();
		String s(n, '\0');
		file.read(s.data(), n);
		Parser p(s, filename);
		bool ret = p.parse(_data);
		file.close();
		return ret;
	}
}
