#include "stylerwindow.h"
#include "ui_stylerwindow.h"

StylerWindow::StylerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StylerWindow)
{
    ui->setupUi(this);
	this->styler = Styler::getInstance();
}

StylerWindow::~StylerWindow()
{
	if(file){
		file->close();
		delete file;
	}

	delete ui;
}

StylerWindow *StylerWindow::getInstance(QWidget *parent){
	static StylerWindow *instance = new StylerWindow(parent);
	return instance;
}

void StylerWindow::closeEvent(QCloseEvent *event){
	this->hide();
	event->ignore();
}

void StylerWindow::on_actionFormat_triggered()
{
	QString code = this->ui->plainTextEdit->toPlainText();
	styler->inputCode(code);
	code = styler->formatCode();

	this->ui->plainTextEdit->clear();
	this->ui->plainTextEdit->appendPlainText(code);
}

void StylerWindow::on_actionCompress_triggered()
{
	QString code = this->ui->plainTextEdit->toPlainText();
	styler->inputCode(code);
	code = styler->compressCode();

	this->ui->plainTextEdit->clear();
	this->ui->plainTextEdit->appendPlainText(code);
}

void StylerWindow::resizeEvent(QResizeEvent *event){
	int width = event->size().width() - 20;
	int height = event->size().height() - 50;
	ui->plainTextEdit->resize(width, height);
}

void StylerWindow::on_actionOpen_triggered()
{
	QFileDialog fileDialog;
	QString filePath = fileDialog.getOpenFileName();

	QFile file(filePath);
	file.open(QFile::ReadWrite);

	ui->plainTextEdit->clear();
	QString fileContent(file.readAll());

	ui->plainTextEdit->appendPlainText(fileContent);
	ui->plainTextEdit->moveCursor(QTextCursor::Start);

	file.close();
}
