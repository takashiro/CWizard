#ifndef WRITER_H
#define WRITER_H

#include <QString>

#include <windows.h>

class Writer{
public:
	Writer();
	static Writer *getInstance();

	void setHook(char args = Writer::keyHookEnabled);		//开启全局钩子
	void unsetHook(char args = Writer::keyHookEnabled);		//关闭全局钩子
	bool isKeyboardHooked() const;
	bool isMouseHooked() const;

	//键盘消息处理
	static LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam);
	//鼠标消息处理
	static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	//在当前光标处输入一个字符
	static void inputChar(BYTE ch);
	static void inputChar(QChar ch);

	//判断是否是双元运算符
	static bool isBioperator(DWORD vkCode);
	static bool isBioperator(QChar vkCode);

	//一些用于方便阅读的常量
	static const char keyHookEnabled = 0x1;		//开启键盘钩子
	static const char mouseHookEnabled = 0x2;	//开启鼠标钩子

private:
	HHOOK keyHook;
	HHOOK mouseHook;

	QString currentLine;
	int currentSpan;
	bool keyboardHooked;
	bool mouseHooked;
};

#endif // WRITER_H
