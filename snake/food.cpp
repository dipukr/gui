#include <math.h>
#include "food.h"
#include "window.h"

Food::Food(int xx, int yy) : x(xx), y(yy) {}

void Food::update(Snake *snake)
{
	while (true) {
		x = rand() % COLS;
		y = rand() % ROWS;
		if (valid(snake, x, y)) break;
	}
}

bool Food::valid(Snake *sn, int x, int y)
{
	for (int a = 0; a < sn->cells.size(); a++) {
		Cell &c = sn->cells.at(a);
		if (c.x == x && c.y == y)
			return false;
	}
	return true;
}

void Food::paint(QPainter &pt)
{
	pt.fillRect(x*SIZE, y*SIZE, SIZE-1,SIZE-1, Qt::blue);
}