#include "writer.h"

Writer *writer = NULL;

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

	writer = this;
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
		UnhookWindowsHookEx(key_hook);
		keyboard_hooked = false;
	}

	if((args & mouseHookEnabled) == mouseHookEnabled){
		UnhookWindowsHookEx(mouse_hook);
		mouse_hooked = false;
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

	/*const DWORD tid = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    AttachThreadInput(tid, GetCurrentThreadId(), true);
    HWND hwnd = GetFocus();
	WCHAR text[255];
	GetWindowText(hwnd, text, sizeof(text));
	qWarning("Title:%s", QString::fromWCharArray(text).toStdString().c_str());*/

	//在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
	KBDLLHOOKSTRUCT *key = (KBDLLHOOKSTRUCT *) lParam;

	qWarning("vkCode: %d", (int) key->vkCode);

	//转换为ASCII
	if(wParam == WM_KEYUP){
		BYTE buffer[300] = {0};
		WORD ch;
		GetKeyboardState(buffer);
		ToAscii(key->vkCode, key->scanCode, buffer, &ch, 0);
		writer->recordChar(QChar::fromAscii(ch));
	}

	bool result = writer->keyHandler(wParam == WM_KEYDOWN ? Writer::KeyDown : Writer::KeyUp, key->vkCode);
	if(!result){
		return CallNextHookEx(writer->key_hook, nCode, wParam, lParam);
	}else{
		return 1;
	}
}

LRESULT CALLBACK Writer::mouseProc(int nCode, WPARAM wParam, LPARAM lParam){
	Writer *writer = Writer::getInstance();
	if(nCode < 0 || writer->isDisabled()){
		return CallNextHookEx(writer->key_hook, nCode, wParam, lParam);;
	}

	writer->clearCurrentLine();

	return CallNextHookEx(writer->mouse_hook, nCode, wParam, lParam);
}

bool Writer::keyHandler(Writer::KeyEvent event, unsigned int key){
	QChar ch = curChar();
	if(event == KeyDown){
		switch(key){
		//键盘状态控制
		case VK_SHIFT:case VK_LSHIFT:case VK_RSHIFT:
			setShiftDown(true);
			return false;
		case VK_CONTROL:case VK_MENU:
			setCtrlDown(true);
			return false;
		}

		if(!isShiftDown()){
			switch(key){
			//双元运算符
			case 107:case 109:case 110:case 111://小键盘四则运算
			case 191:case 187:case 189:
				if(!ch.isSpace()){
					emit styleWarning(tr("CodeStyleError:bioperator"));
					setDisabled();
					inputSpace(1);
					sendKeyEvent(key);
					inputSpace(1);
					setEnabled();
					return true;
				}
			}
		}else{

		}

	}else{
		switch(key){
		//键盘状态控制
		case VK_SHIFT:case VK_LSHIFT:case VK_RSHIFT:
			setShiftDown(false);
			break;
		case VK_CONTROL:case VK_MENU:
			setCtrlDown(false);
			break;
		}

		if(isCtrlDown()){
			return false;
		}

		/*
		if(!isShiftDown()){
			switch(key){
			//逗号运算符
			case 188:
				inputSpace();
				break;

			case 186:
				createNewLine();
			}
		}else{
			switch(key){
			case 219://左侧大括号
				changeCurrentSpan(1);
				createNewLine();
				break;

			case 221://右侧大括号
				setDisabled();
				changeCurrentSpan(-1);
				sendKeyEvent(VK_LEFT);
				sendKeyEvent(VK_LEFT);
				sendKeyEvent(221);
				sendKeyEvent(VK_RETURN);
				setEnabled();
				break;
			}
		}*/
	}

	return false;
}

void Writer::inputSpace(int num){
	if(num < 0){
		num = current_span * 4;
	}

	while(num-- > 0){
		sendKeyEvent(VK_SPACE);
	}
}

void Writer::inputTab(int num){
	if(num < 0){
		num = current_span;
	}
	while(num-- > 0){
		sendKeyEvent(VK_TAB);
	}
}

void Writer::createNewLine(){
	sendKeyEvent(VK_RETURN);

	int	num = current_span;
	while(num-- > 0){
		sendKeyEvent(VK_TAB);
	}
}

void Writer::sendKeyEvent(UINT vkCode){
	UINT uScan = MapVirtualKey(vkCode, 0);
	keybd_event(vkCode, uScan, 0, 0);
	keybd_event(vkCode, uScan, KEYEVENTF_KEYUP, 0);
}

void Writer::wrapSpace(){
	sendKeyEvent(VK_LEFT);
	sendKeyEvent(VK_SPACE);
	sendKeyEvent(VK_RIGHT);
	sendKeyEvent(VK_SPACE);
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

void Writer::recordChar(QChar ch){
	current_line.append(ch);

	if(current_line.length() > 100){
		current_line.remove(0, 1);
	}

	qWarning("char: %c", ch.toAscii());
}

QChar Writer::prevChar() const{
	return current_line.at(current_line.length() - 2);
}

QChar Writer::curChar() const{
	return current_line.at(current_line.length() - 1);
}

void Writer::clearCurrentLine(){
	current_line.clear();
}
