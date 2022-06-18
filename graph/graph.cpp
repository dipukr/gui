#include "graph.h"

Graph::Graph() {
	nodes = new QList<Node*>();
	edges = new QList<Edge*>();
}

void Graph::addNode(Node *node) {nodes->append(node);}
void Graph::addEdge(Edge *edge) {edges->append(edge);}
	
void Graph::paint(QPainter *pt) {
	for (int i = 0; i < nodes->size(); i++)
		nodes->at(i)->paint(pt);
	for (int i = 0; i < edges->size(); i++)
		edges->at(i)->paint(pt);
}

Node* Graph::nodeAt(double x, double y) {
	for (int i = 0; i < nodes->size(); i++) {
		Point *p = nodes->at(i)->pos;
		double d = (x-p->x)*(x-p->x) + (y-p->y)*(y-p->y);
		if (d <= NODE_RADIUS*NODE_RADIUS)
			return nodes->at(i); 
	}
	return 0;
}