#ifndef WRITER_H
#define WRITER_H

#include <QString>
#include <windows.h>

class Writer{
public:
	Writer();
	~Writer();
	static Writer *getInstance();

	void setHook(char args = Writer::keyHookEnabled);		//����ȫ�ֹ���
	void unsetHook(char args = Writer::keyHookEnabled);		//�ر�ȫ�ֹ���
	bool isKeyboardHooked() const;
	bool isMouseHooked() const;

	//������Ϣ����
	static LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam);
	//�����Ϣ����
	static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	//��������
	static void sendKeyEvent(UINT vkCode);

	void inputSpace(int num = 1);
	void wrapSpace();
	void inputTab(int num = -1);
	void createNewLine();

	//һЩ���ڷ����Ķ��ĳ���
	static const char keyHookEnabled;		//�������̹���
	static const char mouseHookEnabled;		//������깳��

	//���ü���״̬
	void setShiftDown(bool value);
	bool isShiftDown() const;

	void setCtrlDown(bool value);
	bool isCtrlDown() const;

	bool isDisabled() const;
	void setEnabled();
	void setDisabled();

	int currentSpan() const;
	void changeCurrentSpan(int change);


private:
	HHOOK key_hook;
	HHOOK mouse_hook;

	QString current_line;
	int current_span;
	bool keyboard_hooked;
	bool mouse_hooked;

	//����״̬
	bool shift_down;
	bool ctrl_down;
	bool is_disabled;
};

#endif // WRITER_H
