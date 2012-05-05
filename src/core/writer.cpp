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

	connect(this, SIGNAL(styleWarning(HabitType)), this, SLOT(convertStyleWarning(HabitType)));
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
#ifdef Q_OS_WIN
		key_hook = SetWindowsHookEx(WH_KEYBOARD_LL, Writer::keyProc, GetModuleHandle(NULL), 0);
#endif
		keyboard_hooked = true;
	}

	if((args & mouseHookEnabled) == mouseHookEnabled){
#ifdef Q_OS_WIN
		mouse_hook = SetWindowsHookEx(WH_MOUSE_LL, Writer::mouseProc, GetModuleHandle(NULL), 0);
#endif
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

#ifdef Q_OS_WIN
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

	//qWarning("vkCode: %d", (int) key->vkCode);

	bool result = false;

	//转换为ASCII
	if(wParam == WM_KEYUP){
		if(key->vkCode != VK_BACK){
			BYTE buffer[300] = {0};
			WORD ch[2];
			GetKeyboardState(buffer);
			if(ToAscii(key->vkCode, key->scanCode, buffer, ch, 0) == 1){
				writer->recordChar(QChar::fromAscii(ch[0]));
				result = writer->keyHandler(wParam == WM_KEYDOWN ? Writer::KeyDown : Writer::KeyUp, key->vkCode);
			}
		}else{
			writer->removeLastChar();
		}
	}

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
#endif

bool Writer::keyHandler(Writer::KeyEvent event, unsigned int key){
	QChar cur = curChar();
	QChar pre = prevChar();
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


		if(!isShiftDown()){
			//处理双元运算符
			if(pre.category() == QChar::Symbol_Math && cur.isLetterOrNumber()){
				QChar tmp = prevChar(2);
				if(tmp.isSymbol()){
					int i = 3;
					do{
						tmp = prevChar(i);
					}while(!tmp.isNull() && tmp.isSymbol());

					if(!tmp.isNull() && !tmp.isSpace()){
						emit styleWarning(Bioperator);

						setDisabled();
						sendKeyEvent(VK_LEFT, i);
						inputSpace(1);
						sendKeyEvent(VK_RIGHT, i - 1);
						inputSpace(1);
						sendKeyEvent(VK_RIGHT);
						setEnabled();
					}
				}else if(!tmp.isSpace()){
					emit styleWarning(Bioperator);

					setDisabled();
					sendKeyEvent(VK_LEFT, 2);
					inputSpace(1);
					sendKeyEvent(VK_RIGHT);
					inputSpace(1);
					sendKeyEvent(VK_RIGHT);
					setEnabled();
				}
			}else if(pre == ',' && cur != ' '){
				emit styleWarning(Comma);

				setDisabled();
				sendKeyEvent(VK_LEFT);
				inputSpace(1);
				sendKeyEvent(VK_RIGHT);
				setEnabled();
			}else if(cur == '"'){

			}else if(cur == '\''){

			}
		}else{

		}
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

void Writer::sendKeyEvent(UINT vkCode, int times){
	UINT uScan = MapVirtualKey(vkCode, 0);
	while(times--){
		keybd_event(vkCode, uScan, 0, 0);
		keybd_event(vkCode, uScan, KEYEVENTF_KEYUP, 0);
	}
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
}

void Writer::removeLastChar(){
	current_line.remove(current_line.length() - 1, 1);
}

QChar Writer::prevChar(int i) const{
	return current_line.at(current_line.length() - 1 - i);
}

QChar Writer::curChar() const{
	return current_line.at(current_line.length() - 1);
}

void Writer::clearCurrentLine(){
	current_line.clear();
	writing_status = None;
}

void Writer::convertStyleWarning(HabitType type){
	switch(type){
	case Bioperator:
		emit styleWarning(tr("Code Style Error: Bioperator"));
		break;
	case Comma:
		emit styleWarning(tr("Code Style Error: Comma"));
		break;
	case Brace:
		emit styleWarning(tr("Code Style Error: Brace"));
		break;
	default:;
	}
}
