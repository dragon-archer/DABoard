#ifndef _DABOARD_PCH_H_
#define _DABOARD_PCH_H_

#ifndef NDEBUG
	#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
	#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_WARN
#endif

#include <cctype>
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>

#include <QApplication>
#include <QHeaderView>
#include <QFile>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QTableWidget>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#endif // _DABOARD_PCH_H_
