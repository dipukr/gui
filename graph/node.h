#pragma once
#include "point.h"
#include <QList>
#include <QPainter>
#define NODE_RADIUS 10

struct Edge;

struct Node
{
	Point *pos;
	QList<Edge*> *edges;

	Node(Point *pos);
	void paint(QPainter *pt);
};
