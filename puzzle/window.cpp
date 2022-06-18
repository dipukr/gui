#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QFile>
#include <QIcon>
#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
	setFixedSize(600, 600);
	setWindowIcon(QIcon(":data/icon.png"));
	init();
}

void Window::init()
{
	QGridLayout *grid = new QGridLayout;
	tiles = new QPushButton*[9];
	grid->setMargin(5);
	for (int i = 0; i < 9; i++) {
		tiles[i] = new QPushButton(QString::number(i));
		auto effect = new QGraphicsDropShadowEffect();
		effect->setBlurRadius(15);
		effect->setOffset(0, 4);
		tiles[i]->setGraphicsEffect(effect);
	}
	//grid->addWidget(tiles[0], 0, 0, 1, 1);
	grid->addWidget(tiles[1], 0, 1, 1, 1);
	grid->addWidget(tiles[2], 0, 2, 1, 1);
	grid->addWidget(tiles[3], 1, 0, 1, 1);
	grid->addWidget(tiles[4], 1, 1, 1, 1);
	grid->addWidget(tiles[5], 1, 2, 1, 1);
	grid->addWidget(tiles[6], 2, 0, 1, 1);
	grid->addWidget(tiles[7], 2, 1, 1, 1);
	grid->addWidget(tiles[8], 2, 2, 1, 1);
	QFile file(":data/style.css");
	file.open(QFile::ReadOnly);
	setStyleSheet(file.readAll());
	setLayout(grid);
}

void Window::keyPressEvent(QKeyEvent *evt)
{
	auto dir(0);
	switch (evt->key()) {
	case Qt::Key_Up: dir = UP; break;
	case Qt::Key_Down: dir = DOWN; break;
	case Qt::Key_Left: dir = LEFT; break;
	case Qt::Key_Right: dir = RIGHT; break;
	}
}
