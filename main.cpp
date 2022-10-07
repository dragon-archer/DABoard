#include "pch.h"
#include "config.h"
#include "datastore.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
	// Init spdlog
	spdlog::set_level(DEFAULT_LOG_LEVEL);
	spdlog::set_pattern(DEFAULT_LOG_PATTERN);

	QApplication a(argc, argv);

	auto& ds = da::DataStore::getInstance();
	ds.readData(DEFAULT_DATAFILE);
	spdlog::debug(ds.data().dump(4));

	MainWindow w;
	w.show();
	return a.exec();
}
