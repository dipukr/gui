#include <QApplication>
#include <QFile>
#include "window.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	MainWindow window;
	QFile file("data/style.css");
	if (!file.open(QIODevice::ReadOnly)) app.quit();
	qApp->setStyleSheet(file.readAll());
	// QStringList args = app.arguments();
	// args.takeFirst();
	// for (auto arg: args)
	// 	window.openFile(arg);
	window.openFile("main.cpp");
	window.openFile("code.pro");
	window.openFile("data/style.css");
	window.show();
	return app.exec();
}
