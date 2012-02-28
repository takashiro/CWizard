#include "styler.h"

const QString Styler::varRegExp = "((?:[a-zA-Z0-9_\\x7f-\\xff]+)(?:\\[[a-zA-Z0-9_\\-\\.\\\"\\'\\[\\]\\$\\x7f-\\xff]+\\])*)";

Styler::Styler(){
	this->codeStatus = 0;

	this->optBioperator = true;
	this->optLeftBraceNewLine = false;
	this->optCommaBlank = true;
	this->optBlockAlwaysQuoted = true;
	this->optFunctionsSplitted = true;

	this->mode = CPP;
}

Styler *Styler::getInstance(){
	static Styler *instance = new Styler();
	return instance;
}

void Styler::inputCode(QString code){
	this->code = code;
	this->codeStatus = 0;
}

QString Styler::formatCode(){
	if(codeStatus == 1){
		return code;
	}

	if(code.length() < 1){
		return "";
	}

	QRegExp rx;

	//保护注释 保护字符串
	protectQuoted();

    //去除原有Tab
	code.replace("\\t", "");

	//双元运算符
	code
		.replace(QRegExp("\\s*((?![\\*/])\\*(?![\\*/])|\\+{1,2}|\\-{1,2}(?!\\>)|(?!/)/|\\!\\={1,2}|\\={1,3}|\\|{1,2}|\\?|\\:|\\<{1,2}|\\>{1,2})\\s*"), optBioperator ? " \\1 " : "\\1")
		.replace(" :  : ", "::")
		.replace("- > ", "->")
		.replace(" ++", "++")
		.replace(" --", "--")
		.replace(QRegExp("\\b(public|private|protected)( slots| signals)?\\s*\\:\\s*"), "\\1\\2:\r\n")
	;	

	//左侧大括号
	code.replace(QRegExp("[\\s]*\\{[\\s]*"), optLeftBraceNewLine ? "\r\n{\r\n" : "{\r\n");

	//右侧大括号
	code.replace(QRegExp("\\s*\\}\\s*"), "\r\n}\r\n");
	code.replace(QRegExp("\\}\\s*(else|\\)|catch|finally)"), "}\\1");

	//Block总是括号
	/*
	code = code.replace("(if|while|for|do|try|catch)[^\\{]{1}(.*?)()");
	*/

	//函数块分开
	if(optFunctionsSplitted){
		code.replace(QRegExp("\\}\\s*function"), "}\r\n\r\nfunction");
	}

	//return右侧空格
	code.replace(QRegExp("return[ \\t]*"), "return ");

	//逗号
	if(optCommaBlank){
		code.replace(QRegExp("\\s*\\,\\s*"), ", ");
	}

	//一句一行
	code.replace(QRegExp("\\s*;\\s*"), ";\r\n");
	rx.setPattern("for\\(\\s*(.*)\\s*;\\s*(.*)\\s*;\\s*(.*)\\s*\\)");
	rx.setMinimal(true);
	rx.setPatternSyntax(QRegExp::RegExp2);
	code.replace(rx, "for(\\1; \\2; \\3)");

	//块注释空行
	code.replace(QRegExp("\\*\\/[\r\n]*"), "*/\r\n");
	code.replace(QRegExp("\\r\\n(\\s*//)"), "\r\n\r\n\\1");

	//缩进
	QStringList block = code.split("\r\n");
	int indent = 0;
	for(int i = 0; i < block.length(); i++){
		if(block[i].length() >= 1 && block[i].indexOf("}") != -1){
			indent--;
		}

		for(int k = 0; k < indent; k++){
			block[i].prepend('\t');
		}

		if(block[i].length() >= 1 && block[i].endsWith('{')){
			indent++;

			if(i >= 1 && block[i - 1].length() >= 1 && block[i - 1].indexOf("}") != -1){
				block[i].prepend("\r\n");
				for(int k = 0; k < indent; k++){
					block[i].prepend('\t');
				}
			}
		}
	}
	code = block.join("\r\n");
	code.replace(QRegExp("\\t(public|private|protected)( slots| signals)?\\:"), "\\1\\2:");

	//修正预编译语句
	rx.setPattern(" *#([a-z]+)\\s*\\< (.*) \\>\\s*");
	rx.setPatternSyntax(QRegExp::RegExp2);
	code.replace(rx, "#\\1 <\\2>\r\n");

	//恢复被保护的字符串
	restoreQuoted();

	codeStatus = 1;
	return code;
}

QString Styler::compressCode(){
	if(codeStatus == 2){
		return code;
	}

	//双元运算符
	code.replace(QRegExp("[\\s]*([\\*\\n+\\-\\/\\=]{1})[\\s]*"), "\\1");
	//左侧大括号
	code.replace(QRegExp("[\\s]*\\{[\\s]*"), "{");
	//一句一行
	code.replace(QRegExp("[\\s]*;[\\s]*"), ";");
	//右侧大括号
	code.replace(QRegExp("[\\s]*\\}[\\s]*"), "}");
	//缩进
	code.replace("\\t", "").replace("\\r", "").replace("\\n", "");

	codeStatus = 2;
	return code;
}

QString Styler::getCode() const{
	return code;
}

void Styler::protectQuoted(){
	protectedLine["str"].clear();
	if(!optNoComment){
		protectedLine["cmt"].clear();
	}

	bool inQuotation = false;
	QChar ch = '"';
	int offset = 0, length = 0;
	bool inBlockComment = false;

	for(int i = 0; i < code.length(); i++){
		if(!inQuotation){
			if(code.at(i) == '"' || code.at(i) == '\'' || code.at(i) == '`'){
				inQuotation = true;
				ch = code.at(i);
				offset = i + 1;
			}else if(code.at(i) == '/'){
				if(code.at(i + 1) == '*'){
					inBlockComment = true;
					goto InComment;
				}else if(code.at(i + 1) == '/'){
					inBlockComment = false;
					goto InComment;
				}
				continue;
				InComment:
				inQuotation = true;
				ch = '/';
				offset = i + 2;
			}
		}else{
			if(ch != '/'){
				if(code.at(i) == '\\'){
					i++;
					continue;
				}

				if(code.at(i) == ch){
					length = i - offset;
					protectedLine["str"].append(code.mid(offset, length));
					code.remove(offset, length);
					i -= length;
					inQuotation = false;
				}
			}else{
				if(inBlockComment){
					if(code.at(i) == '*' && code.at(i + 1) == '/'){
						length = i - offset;

						protectedLine["cmt"].append(code.mid(offset, length));
						code = code.remove(offset, length);
						i -= length;
						inQuotation = false;
					}
				}else{
					if(code.at(i) == '\n'){
						length = i - offset;

						protectedLine["cmt"].append(code.mid(offset, length));
						code.remove(offset, length);
						i -= length;
						inQuotation = false;
					}
				}
			}
		}
	}
}

void Styler::setMode(FileMode mode){
	this->mode = mode;
}


void Styler::restoreQuoted(){
	int index = 0;
	const QRegExp quotation("\"\"|''|``");
	while((index = code.indexOf(quotation, index)) != -1){
		QString &str = protectedLine["str"].first();
		code.insert(index + 1, str);
		index += str.length() + 2;
		protectedLine["str"].removeFirst();
	}

	index = 0;
	const QRegExp comment("/\\*\\*/|//\n");
	while((index = code.indexOf(comment, index)) != -1){
		QString &str = protectedLine["cmt"].first();
		code.insert(index + 2, str);
		index += str.length() + 4;
		protectedLine["cmt"].removeFirst();
	}
}

QString Styler::formatCode(QString code, FileMode mode){
	inputCode(code);
	setMode(mode);
	return formatCode();
}

QString Styler::compressCode(QString code, FileMode mode){
	inputCode(code);
	setMode(mode);
	return compressCode();
}
