
#include "dialog/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

	toolMenu = new QMenu();
	toolMenu->addAction("CStyler");
	toolMenu->addAction("About Us");
}

MainWindow::~MainWindow(){
	delete ui;

	if(toolMenu){
		delete toolMenu;
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

void MainWindow::keyPressEvent(QKeyEvent *event){
	this->on_setting_clicked();
}

void MainWindow::on_exit_clicked(){
	settingDialog->close();
	stylerWindow->close();
    this->close();
}

void MainWindow::on_setting_clicked(){
	settingDialog->show();
}

void MainWindow::on_tool_clicked()
{
	toolMenu->show();
}

void MainWindow::showStyler(){
	stylerWindow->show();
}
