#pragma once
#include <QMainWindow>
class QFont;
class QString;
class QKeyEvent;
class QCloseEvent;
class QTextEdit;
class QSplitter;
class QsciLexer;
class QsciLexerCPP;
class QsciLexerPython;
class QsciAPIs;
#include "editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    void closeEvent(QCloseEvent *evt) override;
    void keyPressEvent(QKeyEvent *evt) override;

private slots:
    void handleNew();
    void handleOpen();
    void handleSave();
    void handleSaveAs();
    void handleUndo();
    void handleRedo();
    void handleCut();
    void handleCopy();
    void handlePaste();
    void handleSelectAll();
    void handleRun();
    void handleFont();
    void handleAbout();
    void handleShowLines();
    void handleHideLines();
    void docWasModified();

private:
	QString currFile;
    QsciLexerCPP *lexerc;
	QsciLexerCPP *lexercpp;
	Editor *editor;
	QFont font;
	QTextEdit *console;
	QSplitter *splitter;

    friend struct Editor;
    friend int main(int argc, char **argv);
	
	void construct();
	void updateLexer();
	void updateFile(const QString &filePath);
	void openFile(const QString &filePath);
	void saveFile(const QString &filePath);
};
