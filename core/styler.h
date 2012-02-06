#ifndef STYLER_H
#define STYLER_H

#include <QString>
#include <QList>
#include <QStringList>

class Styler{
private:
	QString code;
	QList<QString> abnormalList;
	short codeStatus;									//0 ԭʼ 1 չ�� 2 ѹ��

	QList<QString> ProtectedStrs;						//�����ַ���
	QList<QString> ProtectedCmts1, ProtectedCmts2;		//����ע��

public:
	bool optBioperator;					//˫Ԫ��������߿ո�
	bool optLeftBraceNewLine;			//�����������һ��
	bool optCommaBlank;					//�����Ҳ�ӿո�
	bool optBlockAlwaysQuoted;			//�����Ҳ�Ӵ�����
	bool optFunctionsSplitted;			//���������
	bool optNoComment;					//ȥ��ע��

	Styler();
	static Styler *getInstance();

	void inputCode(QString code);		//����ԭʼ����
	QString formatCode();				//�淶������
	QString compressCode();				//ѹ������

private:
	void protectQuoted();				//����ע�͡��ַ�����
	void protectQuoted(QString lquote, QString rquote, QList<QString> &list);
	void restoreQuoted();				//��ԭ��������ע�͡��ַ�����
	void restoreQuoted(QString lquote, QString rquote, QList<QString> &list);

	//ת����ʶ��������ʽ
	void convertNomenclature(const char from, const char to);

public:
	//����������ʽ
	static const char CamelCase = 1;
	static const char UnderlineSplitted = 2;
	static const char Pascal = 3;
	static const char Hungary = 4;
};

#endif // STYLER_H
