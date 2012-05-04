#ifndef STYLER_H
#define STYLER_H

#include <QString>
#include <QStringList>
#include <QMap>

#include "structs.h"

class Styler{
private:
	QString code;
	QStringList abnormalList;
	char codeStatus;								//0 原始 1 展开 2 压缩


	//变量命名方式
	enum Nomenclature {CamelCase, UnderlineSplitted, Pascal, Hungary};
	Nomenclature nomenclature;
	FileMode mode;

	QMap<QString, QStringList> protectedLine;		//保护字符串/注释

public:
	bool optBioperator;					//双元运算符两边空格
	bool optLeftBraceNewLine;			//左大括号另起一行
	bool optCommaBlank;					//逗号右侧加空格
	bool optBlockAlwaysQuoted;			//单句块也加大括号
	bool optFunctionsSplitted;			//函数间空行
	bool optNoComment;					//去除注释

	Styler();
	static Styler *getInstance();

	void setMode(FileMode ext);			//文件格式
	void inputCode(QString code);		//输入原始代码
	QString formatCode();				//规范化代码
	QString formatCode(QString code, FileMode mode = Text);
	QString compressCode();				//压缩代码
	QString compressCode(QString code, FileMode mode = Text);
	QString getCode() const;
    void convertNomenclature(Styler::Nomenclature from, Styler::Nomenclature to);	//转换标识符命名方式

private:
	void protectQuoted();
	void restoreQuoted();

	static const QString varRegExp;
};

extern Styler *styler;

#endif // STYLER_H
