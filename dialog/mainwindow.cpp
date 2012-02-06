
#include "dialog/mainwindow.h"
#include "ui_mainwindow.h"

#include "core/cwizard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

	this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	CWizard *cwizard = CWizard::getInstance();

	toolMenu = new QMenu();
	toolMenu->addAction(tr("CStyler"));
	toolMenu->addAction(tr("About Us"));

	stylerWindow = StylerWindow::getInstance(this);
	settingDialog = SettingDialog::getInstance(this);
	settingDialog->loadSetting(cwizard->setting);

	tray = Tray::getInstance(this);
	connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
	tray->show();
}

MainWindow::~MainWindow(){
	delete ui;

	if(toolMenu){
		delete toolMenu;
	}
}

MainWindow *MainWindow::getInstance(){
	static MainWindow *instance = new MainWindow();
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

void MainWindow::on_tool_clicked(){
	toolMenu->show();
}

void MainWindow::showStyler(){
	stylerWindow->show();
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
