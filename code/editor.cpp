#include "editor.h"

Editor::Editor(QsciLexerCPP *lexer)
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
	setMarginBackgroundColor(1, QColor("#2D2D2D"));
	setLexer(lexer);
	setStyleSheet("border: none");
}

void Editor::keyPressEvent(QKeyEvent *event) 
{
	QsciScintilla::keyPressEvent(event);
	int line = 0, index = 0;
	if (event->key()==Qt::Key_ParenLeft) {
		getCursorPosition(&line, &index);
		insertAt(")", line, index);
	} else if (event->key()==Qt::Key_BraceLeft) {
		getCursorPosition(&line, &index);
		insertAt("}", line, index);
	} else if (event->key()==Qt::Key_BracketLeft) {
		getCursorPosition(&line, &index);
		insertAt("]", line, index);
	} else if (event->key()==Qt::Key_QuoteDbl) {
		getCursorPosition(&line, &index);
		insertAt("\"", line, index);
	}
}
