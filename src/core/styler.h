#ifndef STYLER_H
#define STYLER_H

#include <QString>
#include <QStringList>
#include <QMap>

class Styler{
private:
	QString code;
	QStringList abnormalList;
	char codeStatus;								//0 ԭʼ 1 չ�� 2 ѹ��


	//����������ʽ
	enum Nomenclature {CamelCase, UnderlineSplitted, Pascal, Hungary};
	Nomenclature nomenclature;

	enum FileExt{PHP, Javascript, CPP, Java};
	FileExt mode;

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

	void inputCode(QString code);		//����ԭʼ����
	QString formatCode();				//�淶������
	QString compressCode();				//ѹ������
	QString getCode() const;
	void setMode(FileExt ext);			//�ļ���ʽ

private:
	void protectQuoted();
	void restoreQuoted();

	void convertNomenclature(Styler::Nomenclature from, Styler::Nomenclature to);	//ת����ʶ��������ʽ

	static const QString varRegExp;
};

#endif // STYLER_H
