#pragma once
#include <QMainWindow>
#include <QWidget>
#include "highlighter.h"
#include "textedit.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);

public slots:
	void about();
	void newFile();
	void openFile(const QString &path = QString());

private:
	void construct();

	TextEdit *editor;
	Highlighter *highlighter;
};
