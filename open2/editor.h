#pragma once
#include <Qsci/qsciscintilla.h>
#include <QKeyEvent>
class MainWindow;

struct Editor : public QsciScintilla
{
	MainWindow *parent;

	Editor(MainWindow *parent);
	void keyPressEvent(QKeyEvent *evt);
};