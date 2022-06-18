#include <QApplication>
#include "window.h"

int main(int argc, char **args) 
{
	QApplication app(argc, args);
	MainWindow window;
	window.show();
	return app.exec();
}
