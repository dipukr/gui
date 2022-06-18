#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include "textedit.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	void setCurrentFileName(const QString &fileName);
public slots:
	void about();
	void newFile();
	void openFile(const QString &path);
	void handleSave();
	void handleOpen();
private:
	void construct();
	QString fileName;
	QAction *saveAction;
	TextEdit *editor;
};
