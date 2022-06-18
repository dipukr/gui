#pragma once
#include <QKeyEvent>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>

struct Editor : public QsciScintilla
{

	Editor(QsciLexerCPP *lexer);
	void keyPressEvent(QKeyEvent *event) override;
};
