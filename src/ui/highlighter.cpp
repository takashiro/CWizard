#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent, FileMode mode)
	: QSyntaxHighlighter(parent)
{
	this->filemode = mode;
	HighlightingRule rule;

	keywordFormat.setForeground(QColor(0x80, 0x80, 0x00));
	QStringList keywordPatterns;
	keywordPatterns << "\\bclass\\b" << "\\bconst\\b" << "\\bexplicit\\b"
					<< "\\bfriend\\b" << "\\binline\\b"	<< "\\bnamespace\\b"
					<< "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
					<< "\\bsignals\\b" << "\\bslots\\b" << "\\bstatic\\b"
					<< "\\btypename\\b"	<< "\\bvolatile\\b" << "\\bnew\\b"
					<< "\\bdelete\\b" << "\\btrue\\b" << "\\bfalse\\b"
					<< "\\bdouble\\b" << "\\bchar\\b" << "\\bthis\\b"
					<< "\\blong\\b" << "\\bshort\\b" << "\\bsigned\\b"
					<< "\\bstruct\\b" << "\\bvoid\\b" << "\\bunion\\b"
					<< "\\bvirtual\\b" << "\\btypedef\\b" << "\\bunsigned\\b"
					<< "\\benum\\b" << "\\bint\\b" << "\\boperator\\b"
					<< "\\btemplate\\b" << "\\bfunction\\b" << "\\busing\\b"
                    << "\\bif\\b" << "\\belse\\b" << "\\belseif\\b"
					<< "\\bswitch\\b" << "\\bcase\\b" << "\\bbreak\\b"
					<< "\\bcontinue\\b" << "\\bfor\\b" << "\\bwhile\\b"
                    << "\\bforever\\b" << "\\btry\\b" << "\\bcatch\\b"
                    << "\\bfinally\\b" << "\\breturn\\n" << "\\btypeof\\b"
                    << "\\binstanceof\\b" << "\\binclude\\b" << "\\brequire\\b";
	foreach(const QString &pattern, keywordPatterns){
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	numberFormat.setForeground(QColor(0x00, 0x00, 0x80));
	rule.pattern = QRegExp("\\b(?:0x)?[0-9]+\\b");
	rule.format = numberFormat;
	highlightingRules.append(rule);

	classFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
	rule.format = classFormat;
	highlightingRules.append(rule);

	quotationFormat.setForeground(Qt::darkGreen);

	functionFormat.setFontItalic(false);
	functionFormat.setForeground(Qt::black);
	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat;
	highlightingRules.append(rule);

    precompileFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("#[a-z]+");
    rule.format = precompileFormat;
    highlightingRules.append(rule);

	singleLineCommentFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("//[^\n]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);

	multiLineCommentFormat.setForeground(Qt::darkGreen);

	commentStartExpression = QRegExp("/\\*");
	commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
	foreach(const HighlightingRule &rule, highlightingRules){
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		int length = expression.matchedLength();

		while (index >= 0) {
            setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}

	int quotationStart = 0, quotationEnd = 0;
	QChar edge = '"';
	bool inQuotation = false;
	for(int i = 0; i < text.length(); i++){
		if(inQuotation && text.at(i) == '\\'){
			i++;
			continue;
		}

		if(!inQuotation){
            if(text.at(i) == '"' || text.at(i) == '\'' || text.at(i) == '`'){
				quotationStart = i;
				inQuotation = true;
				edge = text.at(i);
			}

		}else{
			if(text.at(i) == edge){
				quotationEnd = i;
				inQuotation = false;
				setFormat(quotationStart, quotationEnd - quotationStart + 1, quotationFormat);
			}
		}
	}

	setCurrentBlockState(0);
	int startIndex = 0;
	if(previousBlockState() != 1){
		startIndex = commentStartExpression.indexIn(text);
	}

	while(startIndex >= 0){
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if(endIndex == -1){
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}else{
			commentLength = endIndex - startIndex
							+ commentEndExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}


Highlighter::FileMode Highlighter::fileMode() const{
	return filemode;
}

void Highlighter::setFileMode(FileMode mode){
	this->filemode = mode;
}
