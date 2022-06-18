#include "editor.h"
#include "window.h"
#include <QTextEdit>

Editor::Editor(MainWindow *parent) : parent(parent)
{
	setTabWidth(4);
	setCaretWidth(2);
	setAutoIndent(true);
	setAutoCompletionThreshold(1);
    setAutoCompletionSource(QsciScintilla::AcsAll);
	setWrapMode(QsciScintilla::WrapWord);
	setMarginType(1, QsciScintilla::NumberMargin);
	setMarginWidth(1, 0);
	setMarginLineNumbers(1, true);
	setCallTipsVisible(10);
	setLexer(nullptr);
}
	
void Editor::keyPressEvent(QKeyEvent *evt)
{
	QsciScintilla::keyPressEvent(evt);
	int line = 0, index = 0;
	if (evt->key()==Qt::Key_ParenLeft) {
		getCursorPosition(&line, &index);
		insertAt(")", line, index);
	} else if (evt->key()==Qt::Key_BraceLeft) {
		getCursorPosition(&line, &index);
		insertAt("}", line, index);
	} else if (evt->key()==Qt::Key_BracketLeft) {
		getCursorPosition(&line, &index);
		insertAt("]", line, index);
	} else if (evt->key()==Qt::Key_QuoteDbl) {
		getCursorPosition(&line, &index);
		insertAt("\"", line, index);
	} else if (evt->key() == Qt::Key_Escape) {
		parent->console->setVisible(false);
	}
}
