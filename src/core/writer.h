#ifndef WRITER_H
#define WRITER_H

#include <QString>
#include <QObject>
#include <QtCore>

#ifdef Q_OS_WIN
	#include <windows.h>
#endif

#ifdef Q_OS_LINUX
	//#include
#endif

#ifdef Q_OS_MAC
	//#include
#endif

class Writer: public QObject{
	Q_OBJECT

public:
	enum KeyEvent{KeyDown, KeyUp};

	Writer();
	~Writer();
	static Writer *getInstance();

	void setHook(char args = Writer::keyHookEnabled);		//开启全局钩子
	void unsetHook(char args = Writer::keyHookEnabled);		//关闭全局钩子
	bool isKeyboardHooked() const;
	bool isMouseHooked() const;

	//Windows键盘消息处理
	static LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam);
	//Windows鼠标消息处理
	static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	//键盘消息处理
	bool keyHandler(Writer::KeyEvent event, unsigned int key);
	//鼠标消息处理
	bool mouseHandler();

	//控制输入
	static void sendKeyEvent(UINT vkCode);

	void inputSpace(int num = 1);
	void wrapSpace();
	void inputTab(int num = -1);
	void createNewLine();

	//一些用于方便阅读的常量
	static const char keyHookEnabled;		//开启键盘钩子
	static const char mouseHookEnabled;		//开启鼠标钩子

	//设置键盘状态
	void setShiftDown(bool value);
	bool isShiftDown() const;

	void setCtrlDown(bool value);
	bool isCtrlDown() const;

private:
	bool isDisabled() const;
	void setEnabled();
	void setDisabled();

	int currentSpan() const;
	void changeCurrentSpan(int change);

	void clearCurrentLine();
	void recordChar(QChar ch);
	QChar prevChar() const;
	QChar curChar() const;

	HHOOK key_hook;
	HHOOK mouse_hook;

	QString current_line;
	int current_span;
	bool keyboard_hooked;
	bool mouse_hooked;

	//键盘状态
	bool shift_down;
	bool ctrl_down;
	bool is_disabled;

signals:
	void styleWarning(QString msg);
};

extern Writer *writer;

#endif // WRITER_H
