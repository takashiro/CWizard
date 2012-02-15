#ifndef STYLER_H
#define STYLER_H

#include <QString>
#include <QStringList>

class Styler{
private:
	QString code;
	QStringList abnormalList;
	char codeStatus;								//0 ԭʼ 1 չ�� 2 ѹ��

	QStringList ProtectedStrs;						//�����ַ���
	QStringList ProtectedCmts1, ProtectedCmts2;		//����ע��

public:
	bool optBioperator;					//˫Ԫ��������߿ո�
	bool optLeftBraceNewLine;			//�����������һ��
	bool optCommaBlank;					//�����Ҳ�ӿո�
	bool optBlockAlwaysQuoted;			//�����Ҳ�Ӵ�����
	bool optFunctionsSplitted;			//���������
	bool optNoComment;					//ȥ��ע��

	//����������ʽ
	enum Nomenclature {CamelCase, UnderlineSplitted, Pascal, Hungary};

	Styler();
	static Styler *getInstance();

	void inputCode(QString code);		//����ԭʼ����
	QString formatCode();				//�淶������
	QString compressCode();				//ѹ������
	QString getCode() const;

private:
	void protectQuoted(QRegExp pattern, QStringList &list, int lquoteLength, int rquoteLength);		//����ע�͡��ַ�����
	void restoreQuoted(QString lquote, QString rquote, QStringList &list);			//��ԭ��������ע�͡��ַ�����

	void convertNomenclature(Styler::Nomenclature from, Styler::Nomenclature to);	//ת����ʶ��������ʽ
};

#endif // STYLER_H
