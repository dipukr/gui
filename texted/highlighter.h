#pragma once
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QVector>

class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	Highlighter(QTextDocument *parent = nullptr);

protected:
	void highlightBlock(const QString &text) override;

private:
	struct Rule {
		QRegularExpression pattern;
		QTextCharFormat format;
	};
	
	QVector<Rule> rules;
	
	QTextCharFormat keywordFormat;
	QTextCharFormat commentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;
};