#include <QPen>
#include <QIcon>
#include <QBrush>
#include <QPainter>
#include "window.h"
#include "edge.h"
#include "point.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) 
{
	setFixedSize(WIDTH, HEIGHT);
	setWindowTitle("Graph Editor");
	setStyleSheet("background-color: #34B36E;");
	graph = new Graph;
	dragNode = 0;
	startNode = 0;
	repaint();
}

void MainWindow::paintEvent(QPaintEvent *evt) 
{
	Q_UNUSED(evt);
	QPainter pt(this);
	pt.setRenderHint(QPainter::Antialiasing);
	pt.setPen(QPen(Qt::blue, 3));
	pt.setBrush(QBrush(Qt::blue));
	graph->paint(&pt);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *evt)
{
	int xx = evt->x();
	int yy = evt->y();
	Node *node = graph->nodeAt(xx, yy);
	if (node == 0) {
		Point *pnt = new Point(xx, yy);
		Node *node = new Node(pnt);
		graph->addNode(node);
	} else {
		if (startNode == 0)
			startNode = node;
		else {
			Edge *edge = new Edge(startNode, node);
			graph->addEdge(edge);
			startNode = node;
		}
	}
	repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt)
{
	if (dragNode) {
		int xx = evt->x();
		int yy = evt->y();
		dragNode->pos = new Point(xx, yy);
		repaint();
	}
}

void MainWindow::mousePressEvent(QMouseEvent *evt) 
{
	int xx = evt->x();
	int yy = evt->y();
	Node *node = graph->nodeAt(xx, yy);
	if (node != NULL)
		dragNode = node;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt)
{
	Q_UNUSED(evt);
	dragNode = 0;
}
