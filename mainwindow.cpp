#include "pch.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent) {
	// Basic settings
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	grabKeyboard();
	resize(540, 600);
	_central = new QWidget(this);
	setCentralWidget(_central);
	_menuBar = new QMenuBar(this);
	_menuBar->setGeometry(0, 0, 540, 32);
	setMenuBar(_menuBar);
	_statusBar = new QStatusBar(this);
	_statusBar->setGeometry(0, 576, 540, 24);
	setStatusBar(_statusBar);
	_table = new QTableWidget(_central);
	_table->setRowCount(3);
	_table->setColumnCount(3);
	_table->setGeometry(50, 50, 450, 450);
	_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_table->horizontalHeader()->setVisible(false);
	_table->horizontalHeader()->setHighlightSections(false);
	_table->horizontalHeader()->setDefaultSectionSize(150);
	_table->verticalHeader()->setVisible(false);
	_table->verticalHeader()->setHighlightSections(false);
	_table->verticalHeader()->setDefaultSectionSize(150);

	for(int i = 0; i < _table->rowCount(); ++i) {
		for(int j = 0; j < _table->columnCount(); ++j) {
			auto p = new QTableWidgetItem;
			p->setFlags(Qt::ItemFlag::NoItemFlags);
			_table->setItem(i, j, p);
		}
	}

	connect(_table, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);
}

MainWindow::~MainWindow() {
}

void MainWindow::onCellClicked(int row, int col) {
	spdlog::debug("Cell ({}, {}) clicked", row, col);
}
