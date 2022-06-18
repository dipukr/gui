#include <QPaintEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QIcon>
#include <QPixmap>
#include <QImage>
#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent), gameover(false), running(false) {
	resize(COLS*SIZE, ROWS*SIZE);
	setStyleSheet("background-color: rgb(39,40,34);");
	setWindowTitle("Snake");
	snake = Snake(SIZE);
	dir = Snake::RIGHT;
	snake.grow(Cell(10, 10));
	snake.grow(Cell(10, 10));
	snake.grow(Cell(10, 10));
	id = startTimer(100);
}

void Window::paintEvent(QPaintEvent*) {
	QPainter pt(this);
	pt.setRenderHint(QPainter::Antialiasing);
	food.paint(pt);
	snake.paint(pt);
}

void Window::timerEvent(QTimerEvent*) {
	static int frame = 0;
	if (snake.collison) {
		QString s = QString::number(snake.cells.size()-3);
		setWindowTitle("Game Over! Score: "+s);
		killTimer(id);
		return;
	}
	snake.eat(food);
	snake.move(dir);
	repaint();
	QPixmap pix = grab();
	QImage img = pix.toImage();
	QString fileName = QString::number(frame);
	setWindowTitle(fileName);
	img.save(fileName+".png");
	frame++;
}

void Window::keyPressEvent(QKeyEvent *evt) {
	switch (evt->key()) {
	case Qt::Key_Up: dir = Snake::UP; break;
	case Qt::Key_Down: dir = Snake::DOWN; break;
	case Qt::Key_Left: dir = Snake::LEFT; break;
	case Qt::Key_Right: dir = Snake::RIGHT; break;
	}
}
