#ifndef STYLER_H
#define STYLER_H

#include <QString>
#include <QStringList>

class Styler{
private:
	QString code;
	QStringList abnormalList;
	char codeStatus;								//0 原始 1 展开 2 压缩

	QStringList ProtectedStrs;						//保护字符串
	QStringList ProtectedCmts1, ProtectedCmts2;		//保护注释

public:
	bool optBioperator;					//双元运算符两边空格
	bool optLeftBraceNewLine;			//左大括号另起一行
	bool optCommaBlank;					//逗号右侧加空格
	bool optBlockAlwaysQuoted;			//单句块也加大括号
	bool optFunctionsSplitted;			//函数间空行
	bool optNoComment;					//去除注释

	//变量命名方式
	enum Nomenclature {CamelCase, UnderlineSplitted, Pascal, Hungary};

	Styler();
	static Styler *getInstance();

	void inputCode(QString code);		//输入原始代码
	QString formatCode();				//规范化代码
	QString compressCode();				//压缩代码
	QString getCode() const;

private:
	void protectQuoted(QRegExp pattern, QStringList &list, int lquoteLength, int rquoteLength);		//保护注释、字符串等
	void restoreQuoted(QString lquote, QString rquote, QStringList &list);			//还原被保护的注释、字符串等

	void convertNomenclature(Styler::Nomenclature from, Styler::Nomenclature to);	//转换标识符命名方式
};

#endif // STYLER_H
