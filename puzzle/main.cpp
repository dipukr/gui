#include <QApplication>
#include <QFile>
#include <QIcon>
#include "window.h"

int main(int argc, char **argv)
{
	Q_INIT_RESOURCE(puzzle);
	QApplication app(argc, argv);
	Window window;
	window.show();
	return app.exec();
}