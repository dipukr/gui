#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
	Rule rule;
	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontItalic(true);
	//keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	keywordPatterns << "\\btrue\\b" << "\\bfalse\\b" << "\\bnull\\b"
					<< "\\bimport\\b" << "\\bclass\\b" << "\\bconstruct\\b"
					<< "\\bthis\\b" << "\\bfunction\\b" << "\\bprint\\b"
					<< "\\bassert\\b" << "\\bvar\\b" << "\\bif\\b"
					<< "\\belse\\b" << "\\bwhile\\b" << "\\bfor\\b"
					<< "\\bforeach\\b" << "\\bforever\\b" << "\\brepeat\\b"
					<< "\\buntil\\b" << "\\bval\\b" << "\\bbreak\\b"
					<< "\\bcontinue\\b" << "\\breturn\\b" << "\\band\\b"
					<< "\\bor\\b" << "\\bnot\\b" << "\\bmatch\\b"
					<< "\\bcase\\b" << "\\bdefault\\b" << "\\bint\\b"
					<< "\\bfloat\\b" << "\\bbool\\b";
	
	foreach (const QString &pattern, keywordPatterns) {
		rule.pattern = QRegularExpression(pattern);
		rule.format = keywordFormat;
		rules.append(rule);
	}

	commentFormat.setForeground(Qt::red);
	rule.pattern = QRegularExpression("@[^\n]*");
	rule.format = commentFormat;
	rules.append(rule);

	quotationFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegularExpression("\".*\"");
	rule.format = quotationFormat;
	rules.append(rule);

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(Qt::blue);
	rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat;
	rules.append(rule);
}

void Highlighter::highlightBlock(const QString &text)
{
	foreach (const Rule &rule, rules) {
		QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			setFormat(match.capturedStart(), match.capturedLength(), rule.format);
		}
	}
}
