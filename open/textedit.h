#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QCompleter>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QAbstractItemModel>

class TextEdit : public QTextEdit
{
	Q_OBJECT

public:
	TextEdit(QWidget *parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent *evt) override;
	void focusInEvent(QFocusEvent *evt) override;

private slots:
	void insertCompletion(const QString &completion);

private:
	QString textUnderCursor() const;
	QAbstractItemModel* modelFromFile(const QString &fileName);

private:
	QCompleter *completer;
};