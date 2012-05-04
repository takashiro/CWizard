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
	char codeStatus;								//0 ԭʼ 1 չ�� 2 ѹ��


	//����������ʽ
	enum Nomenclature {CamelCase, UnderlineSplitted, Pascal, Hungary};
	Nomenclature nomenclature;
	FileMode mode;

	QMap<QString, QStringList> protectedLine;		//�����ַ���/ע��

public:
	bool optBioperator;					//˫Ԫ��������߿ո�
	bool optLeftBraceNewLine;			//�����������һ��
	bool optCommaBlank;					//�����Ҳ�ӿո�
	bool optBlockAlwaysQuoted;			//�����Ҳ�Ӵ�����
	bool optFunctionsSplitted;			//���������
	bool optNoComment;					//ȥ��ע��

	Styler();
	static Styler *getInstance();

	void setMode(FileMode ext);			//�ļ���ʽ
	void inputCode(QString code);		//����ԭʼ����
	QString formatCode();				//�淶������
	QString formatCode(QString code, FileMode mode = Text);
	QString compressCode();				//ѹ������
	QString compressCode(QString code, FileMode mode = Text);
	QString getCode() const;
    void convertNomenclature(Styler::Nomenclature from, Styler::Nomenclature to);	//ת����ʶ��������ʽ

private:
	void protectQuoted();
	void restoreQuoted();

	static const QString varRegExp;
};

extern Styler *styler;

#endif // STYLER_H
