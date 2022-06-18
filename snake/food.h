#pragma once
#include <QPainter>
#include <cmath>
#include "snake.h"
#include "window.h"

struct Food
{
	int x;
	int y;

	Food(int x=10, int y=2);
	void update(Snake *snake);
	bool valid(Snake *sn, int x, int y);
	void paint(QPainter &pt);
};
