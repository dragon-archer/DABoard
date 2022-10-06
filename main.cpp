#include "pch.h"
#include "config.h"
#include "datastore.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
	// Init spdlog
#ifndef NDEBUG
	spdlog::set_level(spdlog::level::trace);
#else
	spdlog::set_level(spdlog::level::warn);
#endif

	QApplication a(argc, argv);

	auto& ds = da::DataStore::getInstance();
	ds.readData(DEFAULT_DATAFILE);
	spdlog::debug(ds.data().dump(4));

	MainWindow w;
	w.show();
	return a.exec();
}
