#include <QtGui/QApplication>
#include <QTranslator>

#include "core/cwizard.h"
#include "dialog/mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

	//��ʼ��CWizard�����ó������ơ��汾���Լ�ͼ��
	CWizard *cwizard = CWizard::getInstance();
	a.setApplicationName(cwizard->getAppName());
	a.setApplicationVersion(cwizard->getAppVersion());
	a.setWindowIcon(QIcon("image/trayicon.ico"));

	//���س�������
	QString appLang = cwizard->setting->value("displayLanguage", "zh_CN").toString();
	QTranslator translator;
	if(appLang != "en_US"){
		translator.load("lang/" + appLang + ".qm");
		a.installTranslator(&translator);
	}

	//ʵ����������
	MainWindow *mainWindow = MainWindow::getInstance();
	if(cwizard->setting->value("showToolBarOnStart", false).toBool()){
		mainWindow->show();
	}

	//����
    return a.exec();
}
