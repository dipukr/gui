#pragma once
#include <QList>
#include <QPainter>
#include "food.h"

struct Cell
{
	int x;
	int y;
	Cell(int xx=10, int yy=0) : x(xx), y(yy) {}
};

struct Snake
{
	enum {UP, DOWN, LEFT, RIGHT};
		
	QList<Cell> cells;
	bool collison;
	int size;

	Snake();
	Snake(int sz);

	void move(int dir);
	void eat(Food &food);
	void grow(const Cell &cell);
	void paint(QPainter &pt);
};
