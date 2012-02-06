#include "tray.h"

Tray::Tray(QWidget *mainWindow){
	//系统托盘菜单
	QMenu *contextMenu = new QMenu(mainWindow);

	powerOnAction = contextMenu->addAction(tr("Power On"), mainWindow, SLOT(on_powerOn_clicked()));
	contextMenu->addAction(tr("Popup Bar"), mainWindow, SLOT(show()));
	contextMenu->addAction(tr("Statistics"));
	contextMenu->addAction(tr("Setting"), mainWindow, SLOT(on_setting_clicked()));

	QMenu *toolMenu = new QMenu(contextMenu);
	toolMenu->setTitle(tr("Tools"));
	toolMenu->addAction(tr("CStyler"), mainWindow, SLOT(showStyler()));
	toolMenu->addAction(tr("About Us"));

	contextMenu->addMenu(toolMenu);
	contextMenu->addAction(tr("Exit"), mainWindow, SLOT(on_exit_clicked()));

	CWizard *cwizard = CWizard::getInstance();
	setToolTip(cwizard->getAppName() + " (" + cwizard->getAppVersion() + " Ver.)");

	//系统托盘图标
	setIcon(QIcon("image/trayicon.ico"));
	setContextMenu(contextMenu);
}

Tray *Tray::getInstance(QWidget *parent){
	static Tray *instance = new Tray(parent);
	return instance;
}

void Tray::setPowerOnText(bool on){
	if(!on){
		powerOnAction->setText(tr("Power Off"));
	}else{
		powerOnAction->setText(tr("Power On"));
	}
}
