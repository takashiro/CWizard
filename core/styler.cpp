#include "styler.h"

Styler::Styler(){
	this->codeStatus = 0;

	this->optBioperator = true;
	this->optLeftBraceNewLine = false;
	this->optCommaBlank = true;
	this->optBlockAlwaysQuoted = true;
	this->optFunctionsSplitted = true;
	this->optNoComment = true;
}

void Styler::inputCode(QString code){
	this->code = code;
}

QString Styler::formatCode(){
	if(codeStatus == 1){
		return code;
	}

	if(code.length() < 1){
		return "";
	}

	code = code;

	//保护注释
	if(optNoComment){
		code = code.replace(QRegExp("\\/\\/(?:.*?)[\\r\\n]+"), "\r\n").replace(QRegExp("\\/\\*(?:.*?)\\*\\/"), "");
	}else{
		this->ProtectedCmts1.clear();
		this->ProtectedCmts2.clear();
		protectQuoted("/*", "*/", this->ProtectedCmts1);
		protectQuoted("//", "\r\n", this->ProtectedCmts2);
	}

	//保护字符串
	this->ProtectedStrs.clear();
	protectQuoted("\\\"", "", this->ProtectedStrs);

	code = code.replace("\\t", "");

	//双元运算符
	code = code.replace(QRegExp("[\\s]*([\\*\\+\\-\\/]{1,2}|\\!\\={1,2}|\\={1,3}|[\\|\\&]{1,2}|\\?|\\:|[\\<\\>]{1,2})[\\s]*"), optBioperator ? " \\1 " : "\\1");
	code = code.replace(QRegExp("[\\s]+(\\+\\+|\\-\\-)"), "\\1");
	code = code.replace(QRegExp("(\\+\\+|\\-\\-)[\\s]+"), "\\1");

	//左侧大括号
	code = code.replace(QRegExp("[\\s]*\\{[\\s]*"), optLeftBraceNewLine ? "\r\n{\r\n" : "{\r\n");

	//右侧大括号
	code = code.replace(QRegExp("[\\s]*\\}[\\s]*"), "\r\n}\r\n");
	code = code.replace(QRegExp("\\}[\\s]*(else|\\)|catch|finally)"), "}\\1");

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
	code = code.replace(QRegExp("[\\s]*\\,[\\s]*"), ", ");
	}

	//一句一行
	code = code.replace(QRegExp("[\\s]*;[\\s]*"), ";\r\n");
	code = code.replace(QRegExp("for\\(\\s*(.*?)\\s*;\\s*(.*?)\\s*;\\s*(.*?)\\s*\\)"), "for(\\1; \\2; \\3)");

	//块注释空行
	code = code.replace(QRegExp("\\*\\/[\r\n]*"), "*/\r\n");

	//缩进
	QStringList block = code.split("\r\n");
	int indent = 0;

	for(int i = 0; i < block.length(); i++){
		if(block[i].length() >= 1 && block[i].indexOf("}") != -1){
			indent--;
		}

		for(int k = 0; k < indent; k++){
			block[i] = '\t' + block[i];
		}

		if(block[i].length() >= 1 && block[i].at(block[i].length() - 1) == '{'){
			indent++;
		}
	}

	code = block.join("\r\n");
	codeStatus = 1;

	if(!optNoComment){
		protectQuoted("/*", "*/", this->ProtectedCmts1);
		protectQuoted("//", "\r\n", this->ProtectedCmts2);
	}
	protectQuoted("\\\"", "", this->ProtectedStrs);

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

void Styler::protectQuoted(QString lquote, QString rquote, QList<QString> &list){
	if(rquote == ""){
		rquote = lquote;
	}

	QRegExp pattern;
	pattern.setPattern(lquote + "(.*?)" + rquote);
	int offset = 0;
	while((offset = code.indexOf(pattern)) >= 0){
		list << pattern.capturedTexts();
		code = code.remove(offset + lquote.length(), pattern.matchedLength() - rquote.length());
	}
}

void Styler::restoreQuoted(QString lquote, QString rquote, QList<QString> &list){
	if(rquote == ""){
		rquote = lquote;
	}

	QString quote = lquote + rquote;
	int offset = 0, i = 0;
	while((offset = code.indexOf(quote)) >= 0){
		code = code.insert(offset + lquote.length(), list.at(i));
		i++;
	}
}
