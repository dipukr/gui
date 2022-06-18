#include "node.h"

Node::Node(Point *pos)
{
	this->pos = pos;
	this->edges = new QList<Edge*>();
}

void Node::paint(QPainter *pt)
{
	pt->drawEllipse(pos->x-NODE_RADIUS, pos->y-NODE_RADIUS, NODE_RADIUS*2, NODE_RADIUS*2);
}