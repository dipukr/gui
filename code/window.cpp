#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QFont>
#include <QColor>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QProcess>
#include <QIODevice>
#include <QVBoxLayout>
#include <QTabBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QSizeGrip>
#include "window.h"

MainWindow::MainWindow()
{
	resize(1000,550);
	construct();
	setCentralWidget(tab);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	QApplication::quit();
	event->accept();
}

void MainWindow::fileNew()
{
	menuBar()->hide();
	Editor *editor = new Editor(lexer);
	int index = tab->addTab(editor, "untitled");
	tab->setCurrentIndex(index);
	tab->setTabToolTip(index, "");
	tab->setTabWhatsThis(index, "no");
	connect(editor, SIGNAL(textChanged()), this, SLOT(update()));
}

void MainWindow::fileOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	if (fileName.isEmpty()) return;
	openFile(fileName);
}

void MainWindow::openFile(const QString &filePath)
{
	for (int i = 0; i < tab->count(); ++i)
		if (tab->tabToolTip(i) == filePath)
			return;
	QFile file(filePath);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, "Application", "Cannot read file "+filePath+file.errorString());
        return;
    }
    Editor *editor = new Editor(lexer);
    QString fileName = QFileInfo(filePath).fileName();
    int index = tab->addTab(editor, fileName);
    tab->setCurrentIndex(index);
    tab->setTabToolTip(index, filePath);
    tab->setTabWhatsThis(index, "no");
    connect(editor, SIGNAL(textChanged()), this, SLOT(update()));
	QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    editor->setText(in.readAll());
    QApplication::restoreOverrideCursor();
    updateTabText();
}

void MainWindow::update()
{
	int index = tab->currentIndex();
	if (tab->tabWhatsThis(index) == "no") {
		QString text = tab->tabText(index);
		text += "*";
		tab->setTabText(index,text);
		tab->setTabWhatsThis(index, "yes");
	}
}

void MainWindow::updateTabText()
{
	int index = tab->currentIndex();
	if (tab->tabWhatsThis(index) == "yes") {
		QString text = tab->tabText(index);
		text.remove(text.size()-1,1);
		tab->setTabText(index,text);
		tab->setTabWhatsThis(index, "no");
	}
}

void MainWindow::fileSave()
{
	if (tab->tabToolTip(tab->currentIndex()) == "") {
		fileSaveAs();
		return;
	}
	QString filePath = tab->tabToolTip(tab->currentIndex());
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, "Application", "Cannot write file "+filePath);
        return;
	}
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    Editor *editor = currentEditor();
    out << editor->text();
    QApplication::restoreOverrideCursor();
    updateTabText();
}

void MainWindow::fileSaveAs()
{
	QString fileName = tab->tabText(tab->currentIndex());
	QString filePath = QFileDialog::getSaveFileName(this, "Save "+fileName, "/home/"+fileName);
	if (filePath.isEmpty())
		return;
	QFile file(filePath);
	if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, "Application", "Cannot write file "+filePath);
        return;
	}
	QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    Editor *editor = currentEditor();
    out << editor->text();
    QApplication::restoreOverrideCursor();
    fileName = QFileInfo(filePath).fileName();
    tab->setTabText(tab->currentIndex(), fileName);
    tab->setTabToolTip(tab->currentIndex(), filePath);
    tab->setTabWhatsThis(tab->currentIndex(), "no");
}

void MainWindow::fileSaveAll()
{
	int index = tab->currentIndex();
	for (int i = 0; i < tab->count(); ++i) {
		tab->setCurrentIndex(i);
		if (tab->tabWhatsThis(tab->currentIndex()) != "no")
			fileSave();
	}
	tab->setCurrentIndex(index);
}

void MainWindow::closeFile(int idx)
{
	delete tab->widget(idx);
	if (tab->count() == 0)
		fileNew();
	tab->currentWidget()->setFocus();
}

void MainWindow::fileCloseAll()
{
	while (tab->count() != 1)
		closeFile(tab->currentIndex());
	closeFile(tab->currentIndex());
}

void MainWindow::fileClose()
{
	closeFile(tab->currentIndex());
}

Editor* MainWindow::currentEditor()
{
	QWidget *widget = tab->currentWidget();
	QsciScintilla *editor = static_cast<QsciScintilla*>(widget);
	return editor;
}

void MainWindow::viewShowLineNumbers() {currentEditor()->setMarginLineNumbers(1, true);}
void MainWindow::viewHideLineNumbers() {currentEditor()->setMarginLineNumbers(1, false);}

void MainWindow::construct()
{
	QMenu *fileMenu = new QMenu("File");
	QMenu *editMenu = new QMenu("Edit");
	QMenu *viewMenu = new QMenu("View");
	QMenu *helpMenu = new QMenu("Help");
	
	fileMenu->addAction("New", this, SLOT(fileNew()), Qt::CTRL + Qt::Key_N);
	fileMenu->addAction("Open", this, SLOT(fileOpen()), Qt::CTRL + Qt::Key_O);
	fileMenu->addAction("Save", this, SLOT(fileSave()), Qt::CTRL + Qt::Key_S);
	fileMenu->addAction("SaveAs", this, SLOT(fileSaveAs()), Qt::CTRL + Qt::Key_F);
	fileMenu->addAction("Save All", this, SLOT(fileSaveAll()), Qt::CTRL + Qt::Key_A);
	fileMenu->addSeparator();
	fileMenu->addAction("Close", this, SLOT(fileClose()), Qt::CTRL + Qt::Key_Z);
	fileMenu->addAction("Close All", this, SLOT(fileCloseAll()), Qt::CTRL + Qt::Key_Q);
	editMenu->addAction("Copy", this, SLOT(editCopy()), Qt::CTRL + Qt::Key_C);
	editMenu->addAction("Cut", this, SLOT(editCut()), Qt::CTRL + Qt::Key_X);
	editMenu->addAction("Paste", this, SLOT(editPaste()), Qt::CTRL + Qt::Key_V);
	viewMenu->addAction("Show Line Numbers", this, SLOT(viewShowLineNumbers()), Qt::CTRL + Qt::Key_M);
	viewMenu->addAction("Hide Line Numbers", this, SLOT(viewHideLineNumbers()), Qt::CTRL + Qt::Key_H);
	helpMenu->addAction("About", this, SLOT(helpAbout()), Qt::CTRL + Qt::Key_I);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(editMenu);
	menuBar()->addMenu(viewMenu);
	menuBar()->addMenu(helpMenu);

	tab = new QTabWidget(this);
	lexer = new QsciLexerCPP();

	tab->setMovable(true);
	tab->setTabsClosable(false);
	connect(tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));

	lexer->setFont(QFont("DM Mono", 10));
	apis = new QsciAPIs(lexer);
    apis->load(":D:/Code/program/data/c++.api");
    apis->load(":D:/Code/program/data/qt.api");
	apis->prepare();
}

void MainWindow::editCut() {currentEditor()->cut();}
void MainWindow::editCopy() {currentEditor()->copy();}
void MainWindow::editPaste() {currentEditor()->paste();}

void MainWindow::helpAbout()
{
	qApp->quit();
	QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
	// QLabel *icon = new QLabel;
	// icon->setPixmap(QPixmap(":image/logo.png"));
	// QFont font;
	// font.setPointSize(10);
	// QLabel *text = new QLabel;
	// text->setWordWrap(true);
	// text->setFont(font);
	// text->setText("<b>Author:</b> D2epu<br>"
	// 			  "<b>Copyright(c):</b> D2epu<br>"
	// 			  "<b>Licence:</b> GNU General Public Licence 2<br>"
	// 			  "<b>Repository:</b> www.github.com/D2epu/code");
	// QPushButton *quitButton = new QPushButton("OK");
	// QVBoxLayout *topLayout = new QVBoxLayout;
	// topLayout->setMargin(10);
	// topLayout->setSpacing(10);
	// topLayout->addWidget(icon);
	// topLayout->addWidget(text);
	// QHBoxLayout *bottomLayout = new QHBoxLayout;
	// bottomLayout->addStretch();
	// bottomLayout->addWidget(quitButton);
	// bottomLayout->addStretch();
	// QVBoxLayout *mainLayout = new QVBoxLayout;
	// mainLayout->addLayout(topLayout);
	// mainLayout->addLayout(bottomLayout);
	// QDialog win(this, Qt::WindowCloseButtonHint);
	// win.setWindowIcon(QIcon(":image/about.png"));
	// win.setLayout(mainLayout);
	// connect(quitButton, SIGNAL(clicked()), &win, SLOT(close()));
	// win.exec();
}
