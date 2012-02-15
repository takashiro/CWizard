#include "writer.h"

#include <QDebug>
#include <iostream>

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
	if(nCode < 0){
		return CallNextHookEx(instance->keyHook, nCode, wParam, lParam);
	}

	/*HWND currentbox = GetFocus();
	char buf[255];
	*((LPWORD) buf) = 255;
	SendMessage(currentbox, EM_GETLINE, 0, (LPARAM) buf);
	qWarning(buf);*/

	//在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
	KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;

	if(pkbhs->vkCode == VK_RETURN){
		instance->currentLine.clear();
	}

	return 0;
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
