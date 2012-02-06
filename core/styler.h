#ifndef STYLER_H
#define STYLER_H

#include <QString>
#include <QList>
#include <QStringList>

class Styler{
private:
	QString code;
	QList<QString> abnormalList;
	short codeStatus;									//0 原始 1 展开 2 压缩

	QList<QString> ProtectedStrs;						//保护字符串
	QList<QString> ProtectedCmts1, ProtectedCmts2;		//保护注释

public:
	bool optBioperator;					//双元运算符两边空格
	bool optLeftBraceNewLine;			//左大括号另起一行
	bool optCommaBlank;					//逗号右侧加空格
	bool optBlockAlwaysQuoted;			//单句块也加大括号
	bool optFunctionsSplitted;			//函数间空行
	bool optNoComment;					//去除注释

	Styler();
	static Styler *getInstance();

	void inputCode(QString code);		//输入原始代码
	QString formatCode();				//规范化代码
	QString compressCode();				//压缩代码

private:
	void protectQuoted();				//保护注释、字符串等
	void protectQuoted(QString lquote, QString rquote, QList<QString> &list);
	void restoreQuoted();				//还原被保护的注释、字符串等
	void restoreQuoted(QString lquote, QString rquote, QList<QString> &list);

	//转换标识符命名方式
	void convertNomenclature(const char from, const char to);

public:
	//变量命名方式
	static const char CamelCase = 1;
	static const char UnderlineSplitted = 2;
	static const char Pascal = 3;
	static const char Hungary = 4;
};

#endif // STYLER_H
