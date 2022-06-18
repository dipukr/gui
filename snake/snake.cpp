#include "snake.h"
#include "window.h"

Snake::Snake() {}
Snake::Snake(int sz) : size(sz), collison(false) {}

void Snake::eat(Food &food) {
	if (food.x == cells.at(0).x && food.y == cells.at(0).y) {
		grow(Cell(-1, -1));
		food.update(this);
	}
}

void Snake::grow(const Cell &cell) {
	cells.append(cell);
}


void Snake::paint(QPainter &pt) {
	for (int a = 0; a < cells.size(); a++) {
		Cell &c = cells.at(a);
		pt.fillRect(c.x*size, c.y*size, size-1, size-1, Qt::white);
	}
}

void Snake::move(int dir) {
	for (int a = cells.size() - 1; a > 0; a--) {
		cells[a].x = cells[a - 1].x;
		cells[a].y = cells[a - 1].y;
	}
	switch (dir) {
	case UP:
		cells[0].y--;
		if (cells[0].y <= 0) collison = true;
		break;
	case DOWN:
		cells[0].y++;
		if (cells[0].y > ROWS-2) collison = true;
		break;
	case LEFT:
		cells[0].x--;
		if (cells[0].x <= 0) collison = true;
		break;
	case RIGHT:
		cells[0].x++;
		if (cells[0].x > COLS-2) collison = true;
		break;
	}

}
