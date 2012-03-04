#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent, FileMode mode)
	: QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

	//�ؼ���
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
		commonRules.append(rule);
	}

	//����
	numberFormat.setForeground(QColor(0x00, 0x00, 0x80));
	rule.pattern = QRegExp("\\b(?:0x)?[0-9]+\\b");
	rule.format = numberFormat;
	commonRules.append(rule);

	//Qt��
	classFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
	rule.format = classFormat;
	commonRules.append(rule);

	//Ԥ�������
	processorFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("#[a-z]+");
	rule.format = processorFormat;
	commonRules.append(rule);

	quotationFormat.setForeground(Qt::darkGreen);			//�ַ���
	singleLineCommentFormat.setForeground(Qt::darkGreen);	//����ע��
	multiLineCommentFormat.setForeground(Qt::darkGreen);	//��ע��

	setFileMode(mode);
	setCurrentBlockState(0);
}

void Highlighter::highlightBlock(const QString &text){
	foreach(const HighlightingRule &rule, commonRules + extraRules){
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
			case '"':setCurrentBlockState(1);break;		//����˫�����ַ���״̬
			case '\'':setCurrentBlockState(2);break;	//���ڵ������ַ���״̬
			case '`':setCurrentBlockState(3);break;		//���ڷ������ַ���״̬
			case '/':									//����ע��/������ʽ״̬
				if(text.at(i + 1) == '*'){
					setCurrentBlockState(5);	//��ע��
				}else if(text.at(i + 1) == '/'){
					setCurrentBlockState(6);	//��ע��
				}else if(filemode == JavaScript){
					setCurrentBlockState(4);	//JS����
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


FileMode Highlighter::fileMode() const{
	return filemode;
}

void Highlighter::setFileMode(FileMode mode){
	filemode = mode;
	extraRules.clear();

	HighlightingRule rule;

	//PHP
	if(filemode == PHP){
		//ȫ�ֱ�������
		rule.pattern = QRegExp("\\$\\_[A-Z]+");
		rule.format.setForeground(Qt::darkMagenta);
		extraRules.append(rule);

		//PHPϵͳ��������
		static QStringList funcs;
		if(funcs.isEmpty() && QFile::exists("./php_function.dat")){
			QFile file("./php_function.dat");
			file.open(QFile::ReadOnly);
			funcs = QString(file.readAll()).split(" ");
			file.close();
		}
		if(!funcs.isEmpty()){
			foreach(const QString &func, funcs){
				rule.pattern = QRegExp("\\b" + func + "\\b");
				rule.format.setForeground(Qt::darkBlue);
				extraRules.append(rule);
			}
		}
	}

	rehighlight();
}
