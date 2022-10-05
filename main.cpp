#include "pch.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
	// Init spdlog
#ifndef NDEBUG
	spdlog::set_level(spdlog::level::trace);
#else
	spdlog::set_level(spdlog::level::warn);
#endif

	QApplication a(argc, argv);

	MainWindow w;
	w.show();
	return a.exec();
}
