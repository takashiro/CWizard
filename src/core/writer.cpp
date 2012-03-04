#include "writer.h"

const char Writer::keyHookEnabled = 0x01;
const char Writer::mouseHookEnabled = 0x02;

Writer::Writer(){
	this->keyHook = NULL;
	this->mouseHook = NULL;

	this->currentSpan = 0;

	this->keyboardHooked = false;
	this->mouseHooked = false;
}

Writer::~Writer(){
	if(isKeyboardHooked()){
		unsetHook(Writer::keyHookEnabled);
	}

	if(isMouseHooked()){
		unsetHook(Writer::mouseHookEnabled);
	}
}

Writer *Writer::getInstance(){
	static Writer *instance = new Writer();
	return instance;
}

void Writer::setHook(char args){
	if((args & keyHookEnabled) == keyHookEnabled){
		keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, Writer::keyProc, GetModuleHandle(NULL), 0);
		this->keyboardHooked = true;
	}

	if((args & mouseHookEnabled) == mouseHookEnabled){
		mouseHook = SetWindowsHookEx(WH_MOUSE_LL, Writer::mouseProc, GetModuleHandle(NULL), 0);
		this->mouseHooked = false;
	}
}

void Writer::unsetHook(char args){
	if((args & keyHookEnabled) == keyHookEnabled){
		UnhookWindowsHookEx(this->keyHook);
		this->keyboardHooked = false;
	}

	if((args & mouseHookEnabled) == mouseHookEnabled){
		UnhookWindowsHookEx(this->mouseHook);
		this->mouseHooked = false;
	}
}

bool Writer::isKeyboardHooked() const{
	return keyboardHooked;
}

bool Writer::isMouseHooked() const{
	return mouseHooked;
}

LRESULT CALLBACK Writer::keyProc(int nCode, WPARAM wParam, LPARAM lParam){
	Writer *instance = Writer::getInstance();
	if(nCode < 0 || wParam != WM_CHAR){
		return CallNextHookEx(instance->keyHook, nCode, wParam, lParam);;
	}

	/*HWND curWindow = GetForegroundWindow();
	if(IsWindow(curWindow)){
		DWORD pid = GetWindowThreadProcessId(curWindow, NULL);
		AttachThreadInput(pid, GetCurrentThreadId(), true);
		HWND curBox = GetFocus();
		int iLen = SendMessage(curBox, EM_GETLINECOUNT, 0, 0);
		qWarning("%d", iLen);
	}*/

	HWND curBox = GetFocus();
	int iLen = SendMessage(curBox, EM_GETLINECOUNT, 0, 0);
	qWarning("%d", iLen);

	//在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
	KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;

	if(pkbhs->vkCode == VK_RETURN){
		instance->currentLine.clear();
	}

	return CallNextHookEx(instance->keyHook, nCode, wParam, lParam);;
}

LRESULT CALLBACK Writer::mouseProc(int nCode,WPARAM wParam,LPARAM lParam){
	return 0;
}

bool Writer::isBioperator(DWORD vkCode){
	return isBioperator(QChar::fromAscii(vkCode));
}

bool Writer::isBioperator(QChar vkCode){
	QString bioperators = "+-*/%&|?:=";
	for(int i = 0; i < bioperators.length(); i++){
		if(bioperators.at(i) == vkCode){
			return true;
		}
	}
	return false;
}

void Writer::inputChar(BYTE ch){
	keybd_event(VK_LWIN, 0, 0, 0);
	keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
}

void Writer::inputChar(QChar ch){
	inputChar((BYTE) ch.toAscii());
}
