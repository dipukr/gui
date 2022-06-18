#pragma once
#include "node.h"

class QPainter;

struct Edge
{
	Node *from;
	Node *to;

	Edge(Node *from, Node *to);
	void paint(QPainter *pt);
};
