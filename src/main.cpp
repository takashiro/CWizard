#include <QtGui/QApplication>
#include <QTranslator>

#include "core/cwizard.h"
#include "dialog/mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

	//��ʼ��CWizard�����ó������ơ��汾���Լ�ͼ��
	CWizard cwizard;
	a.setApplicationName(cwizard.getAppName());
	a.setApplicationVersion(cwizard.getAppVersion());
	a.setOrganizationName(cwizard.getOrgName());
	a.setQuitOnLastWindowClosed(false);
	a.setWindowIcon(QIcon("image/trayicon.ico"));

	//���س�������
	QString appLang = cwizard.getSetting("displayLanguage", "zh_CN").toString();
	QTranslator translator;
	if(appLang != "en_US"){
		translator.load("lang/" + appLang + ".qm");
		a.installTranslator(&translator);
	}

	//ʵ����������
	MainWindow w;
	if(cwizard.getSetting("displayToolBarOnStart", false).toBool()){
		w.show();
	}

    //�Ƿ���ʾStyler
    if(cwizard.getSetting("showStylerOnStart", false).toBool()){
        w.showStyler();
    }

	//����
    return a.exec();
}
