#pragma once
#include <QMenu>
#include <QAction>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMainWindow>
#include <Qsci/qsciapis.h>
#include "editor.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	void openFile(const QString &filePath);
	Editor* currentEditor();
	void updateTabText();
	void construct();

protected:
	void closeEvent(QCloseEvent *event) override;

private slots:
	void fileNew();
	void fileOpen();
	void fileSave();
	void fileSaveAs();
	void fileSaveAll();
	void fileClose();
	void fileCloseAll();
	void editCut();
	void editCopy();
	void editPaste();
	void helpAbout();
	void viewShowLineNumbers();
	void viewHideLineNumbers();
	void update();
	void closeFile(int idx);
	
private:
	QTabWidget *tab;
	QsciAPIs *apis;
	QsciLexerCPP *lexer;
};
