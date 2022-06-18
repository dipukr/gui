#include <QFile>
#include <QIODevice>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
	Q_INIT_RESOURCE(open);
	QApplication app(argc, argv);
	MainWindow window;
	window.resize(1000,550);
	window.show();
	if (argc == 2) {
		QString s(argv[1]);
		window.openFile(s);
	}
	return app.exec();
}