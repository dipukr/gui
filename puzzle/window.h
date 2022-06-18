#pragma once
#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>

enum {UP, DOWN, LEFT, RIGHT};

struct Window: QWidget
{
	QPushButton **tiles;
	
	Window(QWidget *parent = 0);
	void init();
	void keyPressEvent(QKeyEvent *evt);
};
