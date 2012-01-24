#include "tray.h"

Tray::Tray(CWizard *cwizard){
	this->cwizard = cwizard;
}

bool Tray::eventFilter(QObject *obj, QEvent *event){
	if(event->MouseButtonDblClick){
		cwizard->mainWindow->show();
	}

	return true;
}
