#include <QtGui/QApplication>
#include <QTranslator>

#include "core/cwizard.h"
#include "dialog/mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

	//初始化CWizard，设置程序名称、版本号以及图标
	CWizard cwizard;
	a.setApplicationName(cwizard.getAppName());
	a.setApplicationVersion(cwizard.getAppVersion());
	a.setOrganizationName(cwizard.getOrgName());
	a.setQuitOnLastWindowClosed(false);
	a.setWindowIcon(QIcon("image/trayicon.ico"));

	//加载程序语言
	QString appLang = cwizard.getSetting("displayLanguage", "zh_CN").toString();
	QTranslator translator;
	if(appLang != "en_US"){
		translator.load("lang/" + appLang + ".qm");
		a.installTranslator(&translator);
	}

	//实例化主窗口
	MainWindow w;
	if(cwizard.getSetting("displayToolBarOnStart", false).toBool()){
		w.show();
	}

    //是否显示Styler
    if(cwizard.getSetting("showStylerOnStart", false).toBool()){
        w.showStyler();
    }

	//结束
    return a.exec();
}
