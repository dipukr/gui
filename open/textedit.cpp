#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QTextCursor>
#include <QRect>
#include <QFont>
#include <QFile>
#include <QBrush>
#include <QPalette>
#include <QGradient>
#include <QFontMetrics>
#include <QByteArray>
#include <QStringList>
#include <QApplication>
#include <QScrollBar>
#include <QStyledItemDelegate>
#include <QStringListModel>
#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent), completer(nullptr)
{
	QFont font;
	font.setFamily("DM Mono");
	font.setStyleHint(QFont::Monospace);
	font.setFixedPitch(true);
	font.setPointSize(10);
	
	QFontMetrics metrics(font);
	setFont(font);
	setTabStopWidth(4*metrics.width(' '));

	QStyledItemDelegate *d = new QStyledItemDelegate(this);
	
	completer = new QCompleter(this);
	completer->setWidget(this);
	completer->popup()->setItemDelegate(d);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->popup()->setObjectName("compl");
	completer->popup()->setAttribute(Qt::WA_TranslucentBackground, true);
	completer->setModel(modelFromFile(":data/dict"));
	completer->popup()->setStyleSheet(
		QString("QAbstractItemView#compl {min-width: 300px;min-height: 200px;")+
		QString("font-family: 'DM Mono'; font-size: 13px;}")+
		QString("QAbstractItemView::item{border: 2px solid red;}")
	);
	QObject::connect(completer, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

void TextEdit::insertCompletion(const QString &completion)
{
	QTextCursor cursor = textCursor();
	int extra = completion.length() - completer->completionPrefix().length();
	
	cursor.movePosition(QTextCursor::Left);
	cursor.movePosition(QTextCursor::EndOfWord);
	cursor.insertText(completion.right(extra));
	
	setTextCursor(cursor);
}

QString TextEdit::textUnderCursor() const
{
	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::WordUnderCursor);
	return cursor.selectedText();
}

void TextEdit::focusInEvent(QFocusEvent *evt)
{
	completer->setWidget(this);
	QTextEdit::focusInEvent(evt);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
	if (completer->popup()->isVisible()) {
		// The following keys are forwarded by the completer to the widget
		switch (e->key()) {
		case Qt::Key_Enter:
		case Qt::Key_Return:
		case Qt::Key_Escape:
		case Qt::Key_Tab:
		case Qt::Key_Backtab:
			e->ignore();
			return; // let the completer do default behavior
		default: break;
	   }
	}
	bool isShortcut = (e->modifiers() & Qt::ControlModifier) && (e->key() == Qt::Key_E); // CTRL+E
	if (!isShortcut) // do not process the shortcut when we have a completer
		QTextEdit::keyPressEvent(e);
	
	const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
	if (ctrlOrShift && e->text().isEmpty())
		return;
	
	static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
	bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
	QString completionPrefix = textUnderCursor();
	
	if (!isShortcut && (hasModifier || e->text().isEmpty() || completionPrefix.length() < 1 || eow.contains(e->text().right(1)))) {
		completer->popup()->hide();
		return;
	}
	if (completionPrefix != completer->completionPrefix()) {
		completer->setCompletionPrefix(completionPrefix);
		completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
	}
	QRect cr = cursorRect();
	cr.setWidth(completer->popup()->sizeHintForColumn(0) + completer->popup()->verticalScrollBar()->sizeHint().width());
	completer->complete(cr); // popup it up
}

QAbstractItemModel* TextEdit::modelFromFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
		return new QStringListModel(completer);
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QStringList words;
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		if (!line.isEmpty())
			words << line.trimmed();
	}
	QApplication::restoreOverrideCursor();
	return new QStringListModel(words, completer);
}