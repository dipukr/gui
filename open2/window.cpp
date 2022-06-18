#include <QtCore>
#include <QtWidgets>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qsciapis.h>
#include "window.h"

MainWindow::MainWindow()
{
	construct();
	connect(editor, SIGNAL(textChanged()), this, SLOT(docWasModified()));
	setCentralWidget(splitter);
	updateFile("");
}

void MainWindow::closeEvent(QCloseEvent *evt)
{
	evt->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *evt)
{
	if (evt->key() == Qt::Key_Escape)
		console->setVisible(false);
}

void MainWindow::handleNew()
{
	editor->clear();
	updateFile("");
}

void MainWindow::handleOpen()
{
	QString filePath = QFileDialog::getOpenFileName(this);
	if (!filePath.isEmpty())
		openFile(filePath);
}

void MainWindow::handleSave()
{
	if (!currFile.isEmpty())
		saveFile(currFile);
}

void MainWindow::handleSaveAs()
{
	QString filePath = QFileDialog::getSaveFileName(this);
	if (!filePath.isEmpty())
		saveFile(filePath);
	updateLexer();
}

void MainWindow::openFile(const QString &filePath)
{
	QFile file(filePath);
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::warning(this, "Application", "Cannot read file "+filePath);
		return;
	}
	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	editor->setText(in.readAll());
	QApplication::restoreOverrideCursor();
	updateFile(filePath);
	updateLexer();	
}

void MainWindow::saveFile(const QString &filePath)
{
	QFile file(filePath);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::warning(this, "Application", "Cannot save file "+filePath);
		return;
	}
	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << editor->text();
	QApplication::restoreOverrideCursor();
	updateFile(filePath);
}

void MainWindow::updateFile(const QString &filePath)
{
	currFile = filePath;
	editor->setModified(false);
	setWindowModified(false);
	QString shownName;
	if (currFile.isEmpty()) shownName = "untitled";
	else shownName = QFileInfo(currFile).fileName();
	setWindowTitle(shownName+"[*]");
}

void MainWindow::updateLexer()
{
	QString suffix = QFileInfo(currFile).suffix();
	if (suffix == "c")
		editor->setLexer(lexerc);
	else if (suffix == "cpp" || suffix == "h")
		editor->setLexer(lexercpp);
	else editor->setLexer(lexerc);
}

void MainWindow::handleRun()
{
	if (!currFile.endsWith(".c") && !currFile.endsWith(".cpp")) return;
	handleSave();
	if (console->isHidden()) console->setVisible(true);
	console->clear();
	repaint();
	QProcess p;
	QString src = currFile, exe;
	if (currFile.endsWith(".c"))
		exe = currFile.mid(0, currFile.length()-2)+".exe";
	else if (currFile.endsWith(".cpp"))
		exe = currFile.mid(0, currFile.length()-4)+".exe";
	p.setWorkingDirectory(QFileInfo(currFile).absolutePath());
	if (currFile.endsWith(".c"))
		p.start("gcc", QStringList() << "-o" << exe << src);
	else p.start("g++", QStringList() << "-o" << exe << "-std=c++11" << src /*<< "-lcoll"*/);
	p.waitForFinished();
	int retval = p.exitCode();
	if (retval == 0 && (currFile.endsWith(".c") || currFile.endsWith(".cpp"))) {
		p.start(exe, QStringList());
		p.waitForFinished();
		retval = p.exitCode();
	}
	if (retval) console->setText(p.readAllStandardError());
	else console->setText(p.readAllStandardOutput());
}

void MainWindow::handleFont()
{
	bool ok = false;
	QFont newfont = QFontDialog::getFont(&ok, font, this);
	if (!ok) return;
	font = newfont;
	editor->setFont(font);
	lexerc->setFont(font);
	lexercpp->setFont(font);
}

void MainWindow::construct()
{
	QMenu *fileMenu = new QMenu("File");
	QMenu *editMenu = new QMenu("Edit");
	QMenu *viewMenu = new QMenu("View");
	QMenu *toolMenu = new QMenu("Tool");
	QMenu *helpMenu = new QMenu("Help");

	fileMenu->addAction("New",        this, SLOT(handleNew()),       Qt::CTRL + Qt::Key_N);
	fileMenu->addAction("Open",       this, SLOT(handleOpen()),      Qt::CTRL + Qt::Key_O);
	fileMenu->addAction("Save",       this, SLOT(handleSave()),      Qt::CTRL + Qt::Key_S);
	fileMenu->addAction("Save as",    this, SLOT(handleSaveAs()),    Qt::CTRL + Qt::Key_Q);
	fileMenu->addAction("Exit",       this, SLOT(quit()),            Qt::CTRL + Qt::Key_T);
	editMenu->addAction("Undo",       this, SLOT(handleUndo()),      Qt::CTRL + Qt::Key_Z);
	editMenu->addAction("Redo",       this, SLOT(handleRedo()),      Qt::CTRL + Qt::Key_D);
	editMenu->addAction("Cut",        this, SLOT(handleCut()),       Qt::CTRL + Qt::Key_X);
	editMenu->addAction("Copy",       this, SLOT(handleCopy()),      Qt::CTRL + Qt::Key_C);
	editMenu->addAction("Paste",      this, SLOT(handlePaste()),     Qt::CTRL + Qt::Key_V);
	editMenu->addAction("Select All", this, SLOT(handleSelectAll()), Qt::CTRL + Qt::Key_A);
	toolMenu->addAction("Build",      this, SLOT(handleRun()),       Qt::CTRL + Qt::Key_B);
	toolMenu->addAction("Font...",    this, SLOT(handleFont()),      Qt::CTRL + Qt::Key_F);
	viewMenu->addAction("Show Lines", this, SLOT(handleShowLines()), Qt::CTRL + Qt::Key_L);
	viewMenu->addAction("Hide Lines", this, SLOT(handleHideLines()), Qt::CTRL + Qt::Key_H);
	helpMenu->addAction("About",      this, SLOT(handleAbout()),     Qt::CTRL + Qt::Key_I);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(editMenu);
	menuBar()->addMenu(viewMenu);
	menuBar()->addMenu(toolMenu);
	menuBar()->addMenu(helpMenu);

	font = QFont("DM Mono", 10);
	
	lexerc = new QsciLexerCPP;
	lexercpp = new QsciLexerCPP;
	
	lexerc->setFont(font);
	lexercpp->setFont(font);
	
	QsciAPIs *capis = new QsciAPIs(lexerc);
	QsciAPIs *cppapis = new QsciAPIs(lexercpp);
	
	capis->load(":D:/Code/program/data/term");
	capis->load(":D:/Code/program/data/c.api");
	capis->load(":D:/Code/program/data/unix.api");
	cppapis->load(":D:/Code/program/data/c.api");
	cppapis->load(":D:/Code/program/data/c++.api");
	
	capis->prepare();
	cppapis->prepare();
		
	editor = new Editor(this);
	editor->setFont(font);
	
	console = new QTextEdit();
	console->setVisible(false);
	console->setReadOnly(true);
	console->setFont(font);
	
	splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(editor);
	splitter->addWidget(console);
	splitter->setSizes(QList<int>() << 374 << 200);
}

void MainWindow::handleUndo() {editor->undo();}
void MainWindow::handleRedo() {editor->redo();}
void MainWindow::handleCut() {editor->cut();}
void MainWindow::handleCopy() {editor->copy();}
void MainWindow::handlePaste() {editor->paste();}
void MainWindow::handleSelectAll() {editor->selectAll();}
void MainWindow::handleHideLines() {editor->setMarginWidth(1, 0);}
void MainWindow::handleShowLines() {editor->setMarginWidth(1, 50);}
void MainWindow::docWasModified() {setWindowModified(editor->isModified());}

void MainWindow::handleAbout()
{
	QLabel *icon = new QLabel;
    icon->setPixmap(QPixmap(":data/logo.png"));

    QFont font;
    font.setPointSize(10);
	QLabel *text = new QLabel;
    text->setWordWrap(true);
    text->setFont(font);
	text->setText("<b>Author:</b> D2epu<br>"
				  "<b>Copyright(c):</b> D2epu<br>"
				  "<b>Licence:</b> GNU General Public Licence 2<br>"
				  "<b>Repository:</b> www.github.com/D2epu/cedit");

    QPushButton *quitButton = new QPushButton("OK");

    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->setMargin(10);
    topLayout->setSpacing(10);
    topLayout->addWidget(icon);
    topLayout->addWidget(text);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(quitButton);
    bottomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

	QDialog win(this, Qt::WindowCloseButtonHint);
	win.setWindowIcon(QIcon(":data/about.png"));

	win.setLayout(mainLayout);
	connect(quitButton, SIGNAL(clicked()), &win, SLOT(close()));
	win.exec();
}
