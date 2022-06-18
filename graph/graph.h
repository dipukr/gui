#pragma once

#include "node.h"
#include "edge.h"
#include <QList>
#include <QPainter>

struct Graph
{
    QList<Node*> *nodes;
    QList<Edge*> *edges;

	Graph();
	void addNode(Node *node);
	void addEdge(Edge *edge);
	void paint(QPainter *pt);
	Node* nodeAt(double x, double y);
};
