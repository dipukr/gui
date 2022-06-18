#include <QApplication>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMenu>
#include <QPoint>
#include <QMainWindow>
#include <QActionEvent>
#include <QContextMenuEvent>

class ListWidget : public QWidget
{
	Q_OBJECT

	QListWidget *listWidget;
	QVBoxLayout *layout;

public:
	ListWidget(QWidget *parent = 0) : QWidget(parent)
	{
		layout = new QVBoxLayout();
		listWidget = new QListWidget();
		listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
		listWidget->addItem("Sunday");
		listWidget->addItem("Monday");
		listWidget->addItem("Tuesday");
		listWidget->addItem("Wednesday");
		listWidget->addItem("Thursday");
		listWidget->addItem("Friday");
		listWidget->addItem("Saturday");
		layout->addWidget(listWidget);
		setLayout(layout);
	}

	void contextMenuEvent(QContextMenuEvent *event) override
	{
		QMenu *menu = new QMenu();
		menu->addAction("Action 1");
		menu->addAction("Action 2");
		menu->addAction("Action 3");
		menu->exec(event->globalPos());
	}

private slots:
	void showContextMenu(const QPoint &pos)
	{
		QPoint globalPos = listWidget->mapToGlobal(pos);
		QMenu *menu = new QMenu();
		menu->addAction("Open");
		menu->addAction("Open file location");
		menu->addAction("Open in file explorer");
		menu->exec(globalPos);
	}	
};

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	app.setStyleSheet("QWidget{font-size: 12px}");
	QMainWindow window;
	window.resize(750,500);
	window.setWindowFlags(Qt::WindowCloseButtonHint);
	QHBoxLayout *layout = new QHBoxLayout;
	ListWidget *wid1 = new ListWidget();
	QListWidget *wid2 = new QListWidget();
	layout->addWidget(wid1);
	layout->addWidget(wid2);
	QWidget *widget = new QWidget;
	widget->setLayout(layout);
	window.setCentralWidget(widget);
	window.show();
	return app.exec();
}

#include "gui.moc"