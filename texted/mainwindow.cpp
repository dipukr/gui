#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QMessageBox>
#include <QApplication>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	construct();
	setCentralWidget(editor);
	setWindowTitle("Syntax Highlighter");
}

void MainWindow::newFile()
{
	editor->clear();
}

void MainWindow::openFile(const QString &path)
{
	QString fileName = path;
	if (fileName.isNull())
		fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Neem Files (*.neem)");
	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (file.open(QFile::ReadOnly | QFile::Text))
			editor->setPlainText(file.readAll());
	}
}

void MainWindow::construct()
{
	QMenu *fileMenu = new QMenu("File", this);
	QMenu *helpMenu = new QMenu("Help", this);
	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(helpMenu);

	fileMenu->addAction("New", this, SLOT(newFile()), QKeySequence::New);
	fileMenu->addAction("Open...", this, SLOT(openFile()), QKeySequence::Open);
	fileMenu->addAction("Exit", qApp, SLOT(quit()), QKeySequence::Quit);
	helpMenu->addAction("About", this, SLOT(about()));
	helpMenu->addAction("About Qt", qApp, SLOT(aboutQt()));

	editor = new TextEdit();
	highlighter = new Highlighter(editor->document());
}

void MainWindow::about()
{
	QMessageBox::about(this, "About Syntax Highlighter",
				"<p>The <b>Syntax Highlighter</b> example shows how " \
				"to perform simple syntax highlighting by subclassing " \
				"the QSyntaxHighlighter class and describing " \
				"highlighting rules using regular expressions.</p>");
}