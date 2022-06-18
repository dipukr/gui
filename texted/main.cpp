#include <QFile>
#include <QIODevice>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
	Q_INIT_RESOURCE(texted);
	QApplication app(argc, argv);
	QFile file(":data/style.css");
	file.open(QIODevice::ReadOnly);
	QString data = file.readAll();
	file.close();
	qApp->setStyleSheet(data);
	MainWindow window;
	window.resize(1000,550);
	window.show();
	return app.exec();
}