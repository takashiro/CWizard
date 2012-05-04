#include "writer.h"

#ifdef Q_OS_WIN32

const char Writer::keyHookEnabled = 0x01;
const char Writer::mouseHookEnabled = 0x02;

Writer::Writer(){
	key_hook = NULL;
	mouse_hook = NULL;

	current_span = 0;
	shift_down = false;
	ctrl_down = false;

	keyboard_hooked = false;
	mouse_hooked = false;

	is_disabled = false;
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
		key_hook = SetWindowsHookEx(WH_KEYBOARD_LL, Writer::keyProc, GetModuleHandle(NULL), 0);
		keyboard_hooked = true;
	}

	if((args & mouseHookEnabled) == mouseHookEnabled){
		mouse_hook = SetWindowsHookEx(WH_MOUSE_LL, Writer::mouseProc, GetModuleHandle(NULL), 0);
		mouse_hooked = false;
	}
}

void Writer::unsetHook(char args){
	if((args & keyHookEnabled) == keyHookEnabled){
		UnhookWindowsHookEx(this->key_hook);
		this->keyboard_hooked = false;
	}

	if((args & mouseHookEnabled) == mouseHookEnabled){
		UnhookWindowsHookEx(this->mouse_hook);
		this->mouse_hooked = false;
	}
}

bool Writer::isKeyboardHooked() const{
	return keyboard_hooked;
}

bool Writer::isMouseHooked() const{
	return mouse_hooked;
}

LRESULT CALLBACK Writer::keyProc(int nCode, WPARAM wParam, LPARAM lParam){
	Writer *writer = Writer::getInstance();
	if(nCode < 0 || writer->isDisabled()){
		return CallNextHookEx(writer->key_hook, nCode, wParam, lParam);;
	}

	//在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
	KBDLLHOOKSTRUCT *key = (KBDLLHOOKSTRUCT *) lParam;
	if(wParam == WM_KEYDOWN){
		switch(key->vkCode){
		//键盘状态控制
		case VK_SHIFT:case VK_LSHIFT:case VK_RSHIFT:
			writer->setShiftDown(true);
			goto EndReturn;
		case VK_CONTROL:case VK_MENU:
			writer->setCtrlDown(true);
			goto EndReturn;
		}

		if(!writer->isShiftDown()){
			switch(key->vkCode){
			//双元运算符
			case 107:case 109:case 110:case 111://小键盘四则运算
			case 191:case 187:case 189:
				writer->setDisabled();
				writer->inputSpace(1);
				writer->sendKeyEvent(key->vkCode);
				writer->inputSpace(1);
				writer->setEnabled();
				return 1;
			}
		}else{

		}

	}else{
		switch(key->vkCode){
		//键盘状态控制
		case VK_SHIFT:case VK_LSHIFT:case VK_RSHIFT:
			writer->setShiftDown(false);
			break;
		case VK_CONTROL:case VK_MENU:
			writer->setCtrlDown(false);
			break;
		}

		if(writer->isCtrlDown()){
			goto EndReturn;
		}

		if(!writer->isShiftDown()){
			switch(key->vkCode){
			//逗号运算符
			case 188:
				writer->inputSpace();
				break;

			case 186:
				writer->createNewLine();
			}
		}else{
			switch(key->vkCode){
			case 219://左侧大括号
				writer->changeCurrentSpan(1);
				writer->createNewLine();
				break;

			case 221://右侧大括号
				writer->setDisabled();
				writer->changeCurrentSpan(-1);
				writer->sendKeyEvent(VK_LEFT);
				writer->sendKeyEvent(VK_LEFT);
				writer->sendKeyEvent(221);
				writer->sendKeyEvent(VK_RETURN);
				writer->setEnabled();
				break;
			}
		}
	}

	qWarning("%d", (int)key->vkCode);

	EndReturn:return CallNextHookEx(writer->key_hook, nCode, wParam, lParam);;
}

LRESULT CALLBACK Writer::mouseProc(int nCode,WPARAM wParam,LPARAM lParam){
	return 0;
}

void Writer::inputSpace(int num){
	if(num < 0){
		num = current_span * 4;
	}

	while(num-- > 0){
		Writer::sendKeyEvent(VK_SPACE);
	}
}

void Writer::inputTab(int num){
	if(num < 0){
		num = current_span;
	}
	while(num-- > 0){
		Writer::sendKeyEvent(VK_TAB);
	}
}

void Writer::createNewLine(){
	Writer::sendKeyEvent(VK_RETURN);

	int	num = current_span;
	while(num-- > 0){
		Writer::sendKeyEvent(VK_TAB);
	}
}

void Writer::sendKeyEvent(UINT vkCode){
	UINT uScan = MapVirtualKey(vkCode, 0);
	keybd_event(vkCode, uScan, 0, 0);
	keybd_event(vkCode, uScan, KEYEVENTF_KEYUP, 0);
}

void Writer::wrapSpace(){
	Writer::sendKeyEvent(VK_LEFT);
	Writer::sendKeyEvent(VK_SPACE);
	Writer::sendKeyEvent(VK_RIGHT);
	Writer::sendKeyEvent(VK_SPACE);
}

void Writer::setShiftDown(bool value){
	shift_down = value;
}

void Writer::setCtrlDown(bool value){
	ctrl_down = value;
}

bool Writer::isShiftDown() const{
	return shift_down;
}

bool Writer::isCtrlDown() const{
	return ctrl_down;
}

int Writer::currentSpan() const{
	return current_span;
}

void Writer::changeCurrentSpan(int change){
	current_span += change;
}

bool Writer::isDisabled() const{
	return is_disabled;
}

void Writer::setEnabled(){
	is_disabled = false;
}

void Writer::setDisabled(){
	is_disabled = true;
}

#endif
