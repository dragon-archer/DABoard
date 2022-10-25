#ifndef _DABOARD_MAINWINDOW_H_
#define _DABOARD_MAINWINDOW_H_

#include "pch.h"
#include "config.h"
#include "datastore.h"
#include "jsonwrapper.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

public Q_SLOTS:
	void onCellClicked(int row, int col);

private:
	void initUi();

private:
	QWidget*	_central;
	QMenuBar*	_menuBar;
	QStatusBar* _statusBar;

	QTableWidget* _table;
};

#endif // _DABOARD_MAINWINDOW_H_
