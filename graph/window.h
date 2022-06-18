#pragma once

#define WIDTH 900
#define HEIGHT 600

#include "node.h"
#include "graph.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>

struct MainWindow : QWidget
{
	Graph *graph;
	Node *dragNode;
	Node *startNode;

	MainWindow(QWidget *parent = 0);
	void paintEvent(QPaintEvent *evt);
	void mouseMoveEvent(QMouseEvent *evt);
	void mousePressEvent(QMouseEvent *evt);
	void mouseReleaseEvent(QMouseEvent *evt);
	void mouseDoubleClickEvent(QMouseEvent *evt);
};
