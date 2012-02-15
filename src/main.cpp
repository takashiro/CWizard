#include <QtGui/QApplication>
#include <QTranslator>

#include "core/cwizard.h"
#include "dialog/mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

	//初始化CWizard，设置程序名称、版本号以及图标
	CWizard *cwizard = CWizard::getInstance();
	a.setApplicationName(cwizard->getAppName());
	a.setApplicationVersion(cwizard->getAppVersion());
	a.setQuitOnLastWindowClosed(false);
	a.setWindowIcon(QIcon("image/trayicon.ico"));

	//加载程序语言
	QString appLang = cwizard->getSetting("displayLanguage", "zh_CN").toString();
	QTranslator translator;
	if(appLang != "en_US"){
		translator.load("lang/" + appLang + ".qm");
		a.installTranslator(&translator);
	}

	//实例化主窗口
	MainWindow *mainWindow = MainWindow::getInstance();
	if(cwizard->getSetting("displayToolBarOnStart", false).toBool()){
		mainWindow->show();
	}

	//结束
    return a.exec();
}
