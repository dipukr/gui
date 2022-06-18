#include "edge.h"
#include <QPainter>

Edge::Edge(Node *from, Node *to) {
	this->from = from;
	this->to = to;
	this->from->edges->append(this);
	this->to->edges->append(this);
}

void Edge::paint(QPainter *pt) {
	pt->drawLine(from->pos->x, from->pos->y, to->pos->x, to->pos->y);
}
