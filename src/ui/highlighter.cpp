#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent, FileMode mode)
	: QSyntaxHighlighter(parent)
{
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
					<< "\\bforeach\\b" << "\\bforever\\b" << "\\btry\\b"
					<< "\\bcatch\\b" << "\\bfinally\\b" << "\\breturn\\n"
					<< "\\btypeof\\b" << "\\binstanceof\\b" << "\\binclude(?:\\_once)?\\b"
					<< "\\brequire(?:\\_once)?\\b" << "\\bbool\\b";
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

    precompileFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("#[a-z]+");
    rule.format = precompileFormat;
    highlightingRules.append(rule);

	quotationFormat.setForeground(Qt::darkGreen);
	singleLineCommentFormat.setForeground(Qt::darkGreen);
	multiLineCommentFormat.setForeground(Qt::darkGreen);

	setFileMode(mode);
	setCurrentBlockState(0);
}

void Highlighter::highlightBlock(const QString &text){
	foreach(const HighlightingRule &rule, highlightingRules){
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		int length = expression.matchedLength();

		while (index >= 0) {
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
			length = expression.matchedLength();
		}
	}

	int blockState = previousBlockState();
	blockState = (blockState >= 1 && blockState <= 6) ? blockState : 0;
	setCurrentBlockState(blockState);
	int offset = 0;
	static const char quoteChar[4] = {'"', '\'', '`', '/'};

	for(int i = 0; i < text.length(); i++){
		if(blockState <= 0){
			switch(text.at(i).toAscii()){
			case '"':setCurrentBlockState(1);break;		//处于双引号字符串状态
			case '\'':setCurrentBlockState(2);break;	//处于单引号字符串状态
			case '`':setCurrentBlockState(3);break;		//处于反引号字符串状态
			case '/':									//处于注释/正则表达式状态
				if(text.at(i + 1) == '*'){
					setCurrentBlockState(5);	//块注释
				}else if(text.at(i + 1) == '/'){
					setCurrentBlockState(6);	//行注释
				}else if(filemode == Javascript){
					setCurrentBlockState(4);	//JS正则
				}
				break;
			default:setCurrentBlockState(0);
			}
			if(currentBlockState() != 0){
				offset = i;
			}

		}else{
			if(blockState >= 1 && blockState <= 4){
				if(text.at(i) == '\\'){
					i++;
					continue;
				}
				if(text.at(i) == quoteChar[blockState - 1]){
					setFormat(offset, i - offset + 1, quotationFormat);
					setCurrentBlockState(0);
				}
			}else if(blockState == 5){
				if(text.at(i) == '*' && text.at(i + 1) == '/'){
					setFormat(offset, i - offset + 2, multiLineCommentFormat);
					setCurrentBlockState(0);
					i++;
				}
			}else if(blockState == 6){
				if(i == text.length() - 1){
					setFormat(offset, i - offset + 1, singleLineCommentFormat);
					setCurrentBlockState(0);
				}
			}
		}

		blockState = currentBlockState();
	}

	if(blockState >= 1 && blockState <= 4){
		setFormat(offset, text.length() - offset, quotationFormat);
	}else if(blockState == 5){
		setFormat(offset, text.length() - offset, multiLineCommentFormat);
	}
}


Highlighter::FileMode Highlighter::fileMode() const{
	return filemode;
}

void Highlighter::setFileMode(FileMode mode){
	filemode = mode;

	HighlightingRule rule;

	//PHP
	if(filemode == PHP){
		rule.pattern = QRegExp("\\$\\_[a-zA-Z0-9_\\x7f-\\xff]+");
		rule.format.setForeground(Qt::darkBlue);
		highlightingRules.append(rule);
	}

	rehighlight();
}
