#include "datastore.h"
#include "pch.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent) {
	initUi();
}

MainWindow::~MainWindow() {
}

void MainWindow::onCellClicked(int row, int col) {
	spdlog::debug("Cell ({}, {}) clicked", row, col);
}

void MainWindow::initUi() {
	auto& profile = GLOBAL_DATA;
	auto& ui	  = *profile.getFirst("ui"s);

#define _LOAD(name) \
	auto name = ui.getFirst<Int>(#name##s)

	_LOAD(rowCount);
	_LOAD(columnCount);
	_LOAD(cellSize);
	_LOAD(leftMargin);
	_LOAD(rightMargin);
	_LOAD(topMargin);
	_LOAD(bottomMargin);
	_LOAD(menuBarHeight);
	_LOAD(statusBarHeight);

	auto w = leftMargin + rightMargin + columnCount * cellSize;
	auto h = menuBarHeight + statusBarHeight + topMargin + bottomMargin + rowCount * cellSize;

	setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	grabKeyboard();
	resize(w, h);
	_central = new QWidget(this);
	setCentralWidget(_central);
	_menuBar = new QMenuBar(this);
	_menuBar->setGeometry(0, 0, w, menuBarHeight);
	setMenuBar(_menuBar);
	_statusBar = new QStatusBar(this);
	_statusBar->setGeometry(0, h - statusBarHeight, w, statusBarHeight);
	setStatusBar(_statusBar);
	_table = new QTableWidget(_central);
	_table->setRowCount(rowCount);
	_table->setColumnCount(columnCount);
	_table->setGeometry(leftMargin, topMargin, columnCount * cellSize, rowCount * cellSize);
	_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_table->horizontalHeader()->setVisible(false);
	_table->horizontalHeader()->setHighlightSections(false);
	_table->horizontalHeader()->setDefaultSectionSize(cellSize);
	_table->verticalHeader()->setVisible(false);
	_table->verticalHeader()->setHighlightSections(false);
	_table->verticalHeader()->setDefaultSectionSize(cellSize);

	for(int i = 0; i < _table->rowCount(); ++i) {
		for(int j = 0; j < _table->columnCount(); ++j) {
			auto p = new QTableWidgetItem;
			p->setFlags(Qt::ItemFlag::NoItemFlags);
			_table->setItem(i, j, p);
		}
	}

	connect(_table, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);

#undef _LOAD
}
