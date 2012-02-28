#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>

#include "core/structs.h"

class QTextDocument;

class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

	Q_PROPERTY(FileMode filemode READ fileMode WRITE setFileMode)

public:
	Highlighter(QTextDocument *parent = 0, FileMode mode = CPP);

	FileMode fileMode() const;
	void setFileMode(FileMode mode);

protected:
	void highlightBlock(const QString &text);

private:
	struct HighlightingRule{
		QRegExp pattern;
		QTextCharFormat format;
	};

	FileMode filemode;

	QVector<HighlightingRule> highlightingRules;

	QTextCharFormat keywordFormat;
	QTextCharFormat classFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat numberFormat;
    QTextCharFormat precompileFormat;
};

#endif // HIGHLIGHTER_H
