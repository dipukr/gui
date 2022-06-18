#pragma once
#define SIZE 25
#define ROWS 35
#define COLS 50
#include "snake.h"
#include "food.h"
#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QTimerEvent>

class Window : public QWidget
{	
	Snake snake;
	Food food;
	int dir;
	int id;
	bool running;
	bool gameover;

public:
	Window(QWidget *parent = 0);
	void paintEvent(QPaintEvent *evt);
	void timerEvent(QTimerEvent *evt);
	void keyPressEvent(QKeyEvent *evt);
};
