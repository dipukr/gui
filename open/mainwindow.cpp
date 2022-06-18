#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QMessageBox>
#include <QApplication>
#include <QTextStream>
#include <QTextDocumentWriter>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	construct();
	setCentralWidget(editor);
	setCurrentFileName(QString());
	connect(editor->document(), SIGNAL(modificationChanged(bool)),
            saveAction, SLOT(setEnabled(bool)));
	connect(editor->document(), SIGNAL(modificationChanged(bool)),
            this, SLOT(setWindowModified(bool)));
    setWindowModified(editor->document()->isModified());
}

void MainWindow::newFile()
{
	editor->clear();
	setCurrentFileName(QString());
}

void MainWindow::handleOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*.*)");
	if (!fileName.isEmpty())
		openFile(fileName);
}

void MainWindow::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    editor->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*]").arg(shownName));
    setWindowModified(false);
}


void MainWindow::openFile(const QString &fileName)
{
	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (file.open(QFile::ReadOnly | QFile::Text))
			editor->setPlainText(file.readAll());
	}
	setCurrentFileName(fileName);
}

void MainWindow::handleSave()
{
	if (fileName.isEmpty())
        return;
    QFile file(fileName);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::warning(this, "Application", "Cannot save file "+fileName);
		return;
	}
	QTextStream out(&file);
	out << editor->toPlainText();
	editor->document()->setModified(false);
	file.flush();
	file.close();
}

void MainWindow::construct()
{
	QMenu *fileMenu = new QMenu("File", this);
	QMenu *helpMenu = new QMenu("Help", this);
	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(helpMenu);

	fileMenu->addAction("New", this, SLOT(newFile()), QKeySequence::New);
	fileMenu->addAction("Open...", this, SLOT(handleOpen()), QKeySequence::Open);
	saveAction = fileMenu->addAction("Save", this, SLOT(handleSave()),   QKeySequence::Save);
	fileMenu->addAction("Exit", qApp, SLOT(quit()), QKeySequence::Quit);
	helpMenu->addAction("About", this, SLOT(about()));

	editor = new TextEdit();
}

void MainWindow::about()
{
	QMessageBox::about(this, "About Syntax Highlighter",
				"<p>The <b>Syntax Highlighter</b> example shows how " \
				"to perform simple syntax highlighting by subclassing " \
				"the QSyntaxHighlighter class and describing " \
				"highlighting rules using regular expressions.</p>");
}