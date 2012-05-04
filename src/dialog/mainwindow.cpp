
#include "dialog/mainwindow.h"
#include "ui_mainwindow.h"

#include "core/cwizard.h"
#include "core/writer.h"
#include "dialog/stylerwindow.h"
#include "dialog/settingdialog.h"
#include "dialog/aboutusdialog.h"
#include "dialog/statdialog.h"
#include "ui/tray.h"

MainWindow *MainWindow::instance = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
	if(instance != NULL){
		qWarning("Multiple MainWindow Constructed");
	}else{
		instance = this;
	}

    ui->setupUi(this);

	this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setFocusPolicy(Qt::NoFocus);

	stylerWindow = StylerWindow::getInstance();

	settingDialog = SettingDialog::getInstance(this);
	settingDialog->loadSetting(Wizard->getSetting());

	tray = Tray::getInstance(this);
	connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
	connect(writer, SIGNAL(styleWarning(QString)), tray, SLOT(alertError(QString)));
	tray->show();

	aboutusDialog = NULL;
	statDialog = NULL;

	move(Wizard->getSetting("popupBar/position", QPoint(0, 0)).toPoint());
}

MainWindow::~MainWindow(){
	Wizard->setSetting("popupBar/position", this->pos());
	delete ui;
	delete stylerWindow;
}

MainWindow *MainWindow::getInstance(){
	return instance;
}

void MainWindow::toggleShow(){
	if(this->isVisible()){
		this->hide();
	}else{
		this->show();
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton){
		dragPosition = QPoint(-1, -1);
		event->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton){
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton){
	if(dragPosition != QPoint(-1, -1))
		this->move(event->globalPos() - dragPosition);
		event->accept();
    }
}

void MainWindow::on_exit_clicked(){
	tray->hide();
	qApp->quit();
}

void MainWindow::on_setting_clicked(){
	settingDialog->show();
}

void MainWindow::showStyler() const{
	stylerWindow->show();
}

void MainWindow::showAboutus(){
	if(aboutusDialog == NULL){
		aboutusDialog = new AboutusDialog(this);
	}

	aboutusDialog->show();
}

void MainWindow::on_hide_clicked(){
	this->hide();
}

void MainWindow::on_powerOn_clicked(){
	static Writer *writer = Writer::getInstance();
	static Tray *tray = Tray::getInstance();

	if(writer->isKeyboardHooked()){
		writer->unsetHook();
		ui->powerOn->setText(tr("Power On"));
		tray->setPowerOnText(true);
	}else{
		writer->setHook();
		ui->powerOn->setText(tr("Power Off"));
		tray->setPowerOnText(false);
	}
}

void MainWindow::trayActivated(QSystemTrayIcon::ActivationReason reason){
	if(reason == QSystemTrayIcon::DoubleClick){
		this->toggleShow();
	}
}

void MainWindow::on_cstyler_clicked()
{
	if(stylerWindow->isHidden()){
		stylerWindow->show();
	}else{
		stylerWindow->hide();
	}
}

void MainWindow::on_stat_clicked(){
	if(statDialog == NULL){
		statDialog = new StatDialog(this);
	}

	statDialog->show();
}
