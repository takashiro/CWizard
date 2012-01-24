#include <QtGui/QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <windows.h>

#include "core/cwizard.h"
#include "core/tray.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setApplicationName("CWizard");
	a.setApplicationVersion("Elf");

	CWizard cwizard;

	//程序图标
	QIcon ico = QIcon("image/trayicon.ico");
	a.setWindowIcon(ico);

	//主窗口
	MainWindow mainWindow;
	cwizard.setMainWindow(&mainWindow);
	mainWindow.setWindowFlags(Qt::FramelessWindowHint);
	mainWindow.setWindowTitle("CWizard");
	mainWindow.setWindowIcon(ico);

	//程序配置
	//mainWindow.show();

	//系统托盘菜单
	QMenu *contextMenu = new QMenu();
	contextMenu->addAction("Power On");
	contextMenu->addAction("Popup Bar", &mainWindow, SLOT(show()));
	contextMenu->addAction("Statistics");
	contextMenu->addAction("Setting", &mainWindow, SLOT(on_setting_clicked()));
	QMenu *toolMenu = new QMenu();
	toolMenu->setTitle("Tools");
	toolMenu->addAction("CStyler", &mainWindow, SLOT(showStyler()));
	toolMenu->addAction("About Us");
	contextMenu->addMenu(toolMenu);
	contextMenu->addAction("Exit", &mainWindow, SLOT(on_exit_clicked()));

	//系统托盘
	QSystemTrayIcon trayIcon;
	trayIcon.setIcon(ico);
	trayIcon.setToolTip("CWizard (" + cwizard.getVersion() + " Ver.)");
	trayIcon.setContextMenu(contextMenu);
	trayIcon.installEventFilter(new Tray(&cwizard));
	trayIcon.show();

    return a.exec();
}
