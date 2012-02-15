#include "stylerwindow.h"
#include "ui_stylerwindow.h"

#include "core/styler.h"

const QString StylerWindow::extFilters =
		tr("C/C++/Java/C#").append(" (*.h *.c *.cpp *.cs *.java);;")
	  + tr("PHP").append(" (*.php *.php3 *php4 *.php5);;")
	  + tr("ASP").append(" (*.asp *.aspx);;")
	  + tr("Javascript").append(" (*.js);;")
	  + tr("Plain Text").append(" (*.txt);;")
	  + tr("Any Files").append(" (*.*)");

StylerWindow::StylerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StylerWindow)
{
    ui->setupUi(this);
	this->styler = Styler::getInstance();

	this->file = new QFile();
}

StylerWindow::~StylerWindow()
{
	if(file){
		if(file->isOpen()){
			file->close();
		}
		delete file;
	}

	delete ui;
}

StylerWindow *StylerWindow::getInstance(QWidget *parent){
	static StylerWindow *instance = new StylerWindow(parent);
	return instance;
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

void StylerWindow::on_actionOpen_triggered(){
	QString dirPath;
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), dirPath, extFilters);
	if(filePath.isNull()){
		return;
	}

	if(file->isOpen()){
		file->close();
	}
	file->setFileName(filePath);
	file->open(QFile::ReadWrite);

	ui->plainTextEdit->clear();
	QString fileContent = QString::fromLocal8Bit(file->readAll());

	ui->plainTextEdit->appendPlainText(fileContent);
	ui->plainTextEdit->moveCursor(QTextCursor::Start);
}
