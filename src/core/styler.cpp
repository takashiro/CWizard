#include "styler.h"

const QString Styler::varRegExp = "((?:[a-zA-Z0-9_\\x7f-\\xff]+)(?:\\[[a-zA-Z0-9_\\-\\.\\\"\\'\\[\\]\\$\\x7f-\\xff]+\\])*)";

Styler::Styler(){
	this->codeStatus = 0;

	this->optBioperator = true;
	this->optLeftBraceNewLine = false;
	this->optCommaBlank = true;
	this->optBlockAlwaysQuoted = true;
	this->optFunctionsSplitted = true;
	this->optNoComment = false;

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

	//保护注释
	if(optNoComment){
		code = code.replace(QRegExp("//(?:.*?)[\\r\\n]+"), "\r\n").replace(QRegExp("\\/\\*(?:.*?)\\*\\/"), "");
	}else{
		this->protectedLine["cmt1"].clear();
		this->protectedLine["cmt2"].clear();

		protectQuoted(QRegExp("/\\*([.\\r\\n]*)\\*/"), this->protectedLine["cmt1"], 2, 2);
		protectQuoted(QRegExp("//(.*)\\r\\n"), this->protectedLine["cmt2"], 2, 2);
	}

	//保护字符串
	this->protectedLine["str"].clear();
	protectQuoted(QRegExp("\"(.*)\""), this->protectedLine["str"], 1, 1);

	code = code.replace("\\t", "");

	//双元运算符
	code = code
		.replace(QRegExp("\\s*((?![\\*/])\\*(?![\\*/])|\\+{1,2}|\\-{1,2}(?!\\>)|(?!/)/|\\!\\={1,2}|\\={1,3}|\\|{1,2}|\\?|\\:|\\<{1,2}|\\>{1,2})\\s*"), optBioperator ? " \\1 " : "\\1")
		.replace(" :  : ", "::")
		.replace("- > ", "->")
	;

	//左侧大括号
	code = code.replace(QRegExp("[\\s]*\\{[\\s]*"), optLeftBraceNewLine ? "\r\n{\r\n" : "{\r\n");

	//右侧大括号
	code = code.replace(QRegExp("\\s*\\}\\s*"), "\r\n}\r\n");
	code = code.replace(QRegExp("\\}\\s*(else|\\)|catch|finally)"), "}\\1");

	//Block总是括号
	/*
	code = code.replace("(if|while|for|do|try|catch)[^\\{]{1}(.*?)()");
	*/

	//函数块分开
	if(optFunctionsSplitted){
		code = code.replace(QRegExp("\\}\\s*function"), "}\r\n\r\nfunction");
	}

	//return右侧空格
	code = code.replace(QRegExp("return[ \\t]*"), "return ");

	//逗号
	if(optCommaBlank){
		code = code.replace(QRegExp("\\s*\\,\\s*"), ", ");
	}

	//一句一行
	code = code.replace(QRegExp("\\s*;\\s*"), ";\r\n");
	rx.setPattern("for\\([\\s\\t\\r\\n]*(.*)[\\s\\t\\r\\n]*;[\\s\\t\\r\\n]*(.*)[\\s\\t\\r\\n]*;[\\s\\t\\r\\n]*(.*)[\\s\\t\\r\\n]*\\)");
	rx.setMinimal(true);
	code = code.replace(rx, "for(\\1; \\2; \\3)");

	//块注释空行
	code = code.replace(QRegExp("\\*\\/[\r\n]*"), "*/\r\n");
	code = code.replace(QRegExp("\\r\\n(\\s*//)"), "\r\n\r\n\\1");

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

		if(block[i].length() >= 1 && block[i].at(block[i].length() - 1) == '{'){
			indent++;
		}
	}

	code = block.join("\r\n");
	codeStatus = 1;

	//if(!optNoComment){
	//	restoreQuoted("/*", "*/", this->protectedLine["cmt1"]);
	//	restoreQuoted("//", "\r\n", this->protectedLine["cmt2"]);
	//}
	//restoreQuoted("\"", "\"", this->protectedLine["str"]);

	return code;
}

QString Styler::compressCode(){
	if(codeStatus == 2){
		return code;
	}

	code = code;

	//双元运算符
	code = code.replace(QRegExp("[\\s]*([\\*\\n+\\-\\/\\=]{1})[\\s]*"), "\\1");
	//左侧大括号
	code = code.replace(QRegExp("[\\s]*\\{[\\s]*"), "{");
	//一句一行
	code = code.replace(QRegExp("[\\s]*;[\\s]*"), ";");
	//右侧大括号
	code = code.replace(QRegExp("[\\s]*\\}[\\s]*"), "}");
	//缩进
	code = code.replace("\\t", "").replace("\\r", "").replace("\\n", "");

	codeStatus = 2;
	return code;
}

QString Styler::getCode() const{
	return code;
}

void Styler::protectQuoted(QRegExp pattern, QStringList &list, int lquoteLength, int rquoteLength){
	pattern.setMinimal(true);

	int index = -1;
	int offset = 0;
	QString capturedText;
	while((index = pattern.indexIn(code, offset)) != -1){
		if(pattern.captureCount() > 1){
			capturedText = pattern.capturedTexts().at(1);
			list.append(capturedText);

			code.remove(index + lquoteLength, capturedText.length());
			offset = index + lquoteLength + rquoteLength;
		}else{
			break;
		}
	}
}

void Styler::restoreQuoted(QString lquote, QString rquote, QStringList &list){
	QString quote = lquote + rquote;
	int offset = 0, i = 0;
	while((offset = code.indexOf(quote, offset)) >= 0 && i < list.length()){
		code = code.insert(offset + lquote.length(), list.at(i));
		offset += lquote.length() + list.at(i).length() + rquote.length();
		i++;
	}
}

void Styler::setMode(FileExt ext){
	this->mode = ext;
}
