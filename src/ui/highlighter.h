#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

	Q_PROPERTY(Highlighter::FileMode filemode READ fileMode WRITE setFileMode)

public:
	enum FileMode{PHP, Java, CPP, Javascript};
    Q_ENUMS(FileMode)

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

	QRegExp commentStartExpression, commentEndExpression;

	QTextCharFormat keywordFormat;
	QTextCharFormat classFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;
	QTextCharFormat numberFormat;
    QTextCharFormat precompileFormat;
};

#endif // HIGHLIGHTER_H
