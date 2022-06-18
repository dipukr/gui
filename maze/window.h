#pragma once
#include <QWidget>
#include <QColor>
#include <QPoint>
#include <QStack>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>

class Window : public QWidget
{
	int *maze;
	int rows, cols;
	QColor wallColor;
	QStack<QPoint> frontier;
	
	int size;
	int margin;
	
public:
	Window(QWidget *parent = 0);
	void load(const QString &fileName);
	void draw(QPainter &pt);
	bool findPath(int r, int c);
	void paintEvent(QPaintEvent *evt);
	void timerEvent(QTimerEvent *evt);
};