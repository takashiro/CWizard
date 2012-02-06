#ifndef WRITER_H
#define WRITER_H

#include <QString>

#include <windows.h>

class Writer{
public:
	Writer();
	static Writer *getInstance();

	void setHook(char args = Writer::keyHookEnabled);		//����ȫ�ֹ���
	void unsetHook(char args = Writer::keyHookEnabled);		//�ر�ȫ�ֹ���
	bool isKeyboardHooked() const;
	bool isMouseHooked() const;

	//������Ϣ����
	static LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam);
	//�����Ϣ����
	static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	//�ڵ�ǰ��괦����һ���ַ�
	static void inputChar(BYTE ch);
	static void inputChar(QChar ch);

	//�ж��Ƿ���˫Ԫ�����
	static bool isBioperator(DWORD vkCode);
	static bool isBioperator(QChar vkCode);

	//һЩ���ڷ����Ķ��ĳ���
	static const char keyHookEnabled = 0x1;		//�������̹���
	static const char mouseHookEnabled = 0x2;	//������깳��

private:
	HHOOK keyHook;
	HHOOK mouseHook;

	QString currentLine;
	int currentSpan;
	bool keyboardHooked;
	bool mouseHooked;
};

#endif // WRITER_H
