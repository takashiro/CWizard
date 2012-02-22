
#include "tray.h"
#include "core/cwizard.h"

Tray::Tray(QWidget *mainWindow){
	setParent(mainWindow);

	//系统托盘菜单
	contextMenu = new QMenu();

	powerOnAction = contextMenu->addAction(tr("Power On"), mainWindow, SLOT(on_powerOn_clicked()));
	contextMenu->addAction(tr("Statistics"));

	contextMenu->addSeparator();

	contextMenu->addAction(tr("Popup Bar"), mainWindow, SLOT(show()));
	contextMenu->addAction(tr("CStyler"), mainWindow, SLOT(showStyler()));

	contextMenu->addSeparator();

	contextMenu->addAction(tr("Settings"), mainWindow, SLOT(on_setting_clicked()));

	QMenu *helpMenu = new QMenu(contextMenu);
	helpMenu->setTitle(tr("Help"));
	helpMenu->addAction(tr("Context Help"));
	helpMenu->addAction(tr("Update"));
	helpMenu->addAction(tr("About Us"), mainWindow, SLOT(showAboutus()));
	contextMenu->addMenu(helpMenu);

	contextMenu->addSeparator();

	contextMenu->addAction(tr("Exit"), mainWindow, SLOT(on_exit_clicked()));

	//系统托盘提示
	setToolTip(Wizard->getAppName() + " " + Wizard->getAppVersion());

	//系统托盘图标
	setIcon(QIcon("image/trayicon.ico"));
	setContextMenu(contextMenu);

	isFirstBoot = true;
}

Tray::~Tray(){
	delete contextMenu;
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

void Tray::show(){
	QSystemTrayIcon::show();

	if(isFirstBoot){
		showMessage(Wizard->getAppName(), tr("Welcome to ") + toolTip(), Information, 2000);
		isFirstBoot = false;
	}
}
