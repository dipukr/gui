#include <QPen>
#include <QRect>
#include <QFile>
#include <QBrush>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>
#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
	size = 30;
	margin = 25;
	wallColor = QColor(39,40,34);
	load("data/maze.mz");
	findPath(1,1);
	setFixedWidth(cols * size + margin * 2);
	setFixedHeight(rows * size + margin * 2);
	setWindowTitle("Count: "+QString::number(frontier.size()));
	startTimer(200);
}

void Window::load(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) return;
	QTextStream in(&file);
	QStringList lines;
	while (!in.atEnd()) {
		QString line = in.readLine();
		if (!line.isEmpty())
			lines << line;
	}
	file.close();
	rows = lines.size();
	cols = lines.at(0).size();
	maze = new int[rows * cols];
	for (int i = 0; i < lines.size(); i++) {
		const QString &line = lines.at(i);
		for (int j = 0; j < line.size(); j++) {
			if (line[j] == '0')
				maze[i * cols + j] = 0;
			else maze[i * cols + j] = 1;
		}
	}
}

void Window::draw(QPainter &pt)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i * cols + j] == 0) {
				pt.setBrush(wallColor);
				pt.setPen(Qt::black);
				pt.drawRect(j*size+margin, i*size+margin, size, size);	
			}
		}
	}
	pt.setBrush(Qt::yellow);
	pt.drawPie((cols-2)*size+margin, (rows-2)*size+margin, size, size, -16*30,16*60);
}

bool Window::findPath(int r, int c)
{
	if (r < rows && r >= 0 && c < cols && c >= 0 && maze[r * cols + c] == 1) {
		if (r == rows-2 && c == cols-2) {
			frontier.push(QPoint(r,c));
			return true;
		}
		maze[r * cols + c] = 2;
		if (findPath(r - 1, c)) {
			frontier.push(QPoint(r,c));
			return true;
		}
		if (findPath(r + 1, c)) {
			frontier.push(QPoint(r,c));
			return true;
		}
		if (findPath(r, c - 1)) {
			frontier.push(QPoint(r,c));
			return true;
		}
		if (findPath(r, c + 1)) {
			frontier.push(QPoint(r,c));
			return true;
		}
	}
	return false;
}

void Window::paintEvent(QPaintEvent *evt)
{
	Q_UNUSED(evt);
	QPainter pt(this);
	pt.setRenderHint(QPainter::Antialiasing);
	draw(pt);
	QPoint p = frontier.pop();
	pt.setBrush(Qt::yellow);
	pt.drawPie(p.y()*size+margin, p.x()*size+margin, size, size, 16*30, 16*300);
}

void Window::timerEvent(QTimerEvent *evt)
{
	Q_UNUSED(evt);
	if (frontier.isEmpty()) return;
	repaint();
}
