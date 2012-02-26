#include "stylerwindow.h"
#include "ui_stylerwindow.h"
#include "settingdialog.h"

#include "core/cwizard.h"
#include "core/styler.h"

#include <QFileInfo>

const QString StylerWindow::extFilters =
        StylerWindow::tr("All Types") + " (*.h *.c *.cpp *.cs *.java *.php *.php3 *php4 *.php5 *.asp *.aspx *.js *.txt);;"
      + "C/C++ (*.h *.c *.cpp);;"
      + "C# (*.cs);;"
      + "Java (*.java);;"
      + "PHP (*.php *.php3 *php4 *.php5);;"
      + "ASP (*.asp *.aspx);;"
      + "Javascript (*.js);;"
      + StylerWindow::tr("Plain Text") + " (*.txt);;"
      + StylerWindow::tr("Any Files") + " (*.*)";

StylerWindow::StylerWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::StylerWindow)
{
    ui->setupUi(this);
	styler = Styler::getInstance();

	file = new QFile();
	setting = Wizard->getSetting();

	setting->beginGroup("styler");

	//����򿪵�·��
	QStringList recentPaths = setting->value("recentPaths").value<QStringList>();
	if(!recentPaths.isEmpty()){
		foreach(QString str, recentPaths){
			Action *action = new Action(str, ui->menuRecentPaths);
			connect(action, SIGNAL(triggered()), action, SLOT(triggerWithText()));
			connect(action, SIGNAL(triggered(QString)), this, SLOT(openFile(QString)));
			ui->menuRecentPaths->addAction(action);
		}
	}else{
		ui->menuRecentPaths->addAction("No recent paths...");
		ui->menuRecentPaths->actions()[0]->setDisabled(true);
	}

	//����򿪵��ļ�
	QStringList recentFiles = setting->value("recentFiles").value<QStringList>();
	if(!recentFiles.isEmpty()){
		foreach(QString str, recentFiles){
			Action *action = new Action(str, ui->menuRecentFiles);
			connect(action, SIGNAL(triggered()), action, SLOT(triggerWithText()));
			connect(action, SIGNAL(triggered(QString)), this, SLOT(openFile(QString)));
			ui->menuRecentFiles->addAction(action);
		}
	}else{
		ui->menuRecentFiles->addAction("No recent files...");
		ui->menuRecentFiles->actions()[0]->setDisabled(true);
	}

	//���ɿ�ݹ�����
	ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	ui->toolBar->addAction(QIcon("./image/toolbar/open.ico"), tr("Open"), this, SLOT(on_actionOpen_triggered()));
	ui->toolBar->addAction(QIcon("./image/toolbar/save.ico"), tr("Save"), this, SLOT(on_actionSave_triggered()));
	ui->toolBar->addSeparator();
	ui->toolBar->addAction(QIcon("./image/toolbar/format.ico"), tr("Format"), this, SLOT(on_actionFormat_triggered()));
	ui->toolBar->addAction(QIcon("./image/toolbar/compress.ico"), tr("Compress"), this, SLOT(on_actionCompress_triggered()));
	ui->toolBar->addAction(QIcon("./image/toolbar/tips.ico"), tr("Tips"));
	ui->toolBar->addSeparator();
	ui->toolBar->addAction(QIcon("./image/toolbar/settings.ico"), tr("Settings"), this, SLOT(on_actionSettings_triggered()));
	ui->toolBar->addAction(QIcon("./image/toolbar/help.ico"), tr("Help"));

	//�������Ƿ�����
	ui->actionLockToolBar->setChecked(setting->value("toolBarLocked").toBool());
	if(ui->actionLockToolBar->isChecked()){
		ui->toolBar->setMovable(false);
	}

	//��ԭ����״̬
	resize(setting->value("windowSize", QSize(500, 300)).toSize());
	move(setting->value("WindowPosition", QPoint(1, 1)).toPoint());
	switch(setting->value("windowState", 1).toInt()){
	case 1:
		setWindowState(Qt::WindowMaximized);
		break;
	case 2:
		setWindowState(Qt::WindowFullScreen);
		break;
	default:;
	}

	//�ź���۵�����
	//connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(hide()));
    connect(ui->actionCut, SIGNAL(triggered()), ui->plainTextEdit, SLOT(cut()));
    connect(ui->actionCopy, SIGNAL(triggered()), ui->plainTextEdit, SLOT(copy()));
    connect(ui->actionPaste, SIGNAL(triggered()), ui->plainTextEdit, SLOT(paste()));
    connect(ui->actionSelectAll, SIGNAL(triggered()), ui->plainTextEdit, SLOT(selectAll()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->plainTextEdit, SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), ui->plainTextEdit, SLOT(redo()));

	setting->endGroup();
}

StylerWindow::~StylerWindow(){
	//��¼����״̬
	setting->beginGroup("styler");
	if(this->windowState() == Qt::WindowNoState){
		setting->setValue("windowSize", QVariant::fromValue(this->size()));
	}
	setting->setValue("WindowPosition", QVariant::fromValue(this->pos()));
	switch(this->windowState()){
	case Qt::WindowMaximized:
		setting->setValue("windowState", 1);
		break;
	case Qt::WindowFullScreen:
		setting->setValue("windowState", 2);
		break;
	default:
		setting->setValue("windowState", 0);
	}
	setting->endGroup();

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

	ui->plainTextEdit->setPlainText(code);
}

void StylerWindow::on_actionCompress_triggered()
{
	QString code = this->ui->plainTextEdit->toPlainText();

	styler->inputCode(code);
	code = styler->compressCode();

	ui->plainTextEdit->setPlainText(code);
}

void StylerWindow::on_actionOpen_triggered(){
	openFile();
}

void StylerWindow::openFile(QString filePath){
	//Ҫ�򿪵��ļ�/Ŀ¼����Ϣ
	QFileInfo info(filePath);

	//���ʹ�õ�·��
	QStringList recentPaths = setting->value("styler/recentPaths").value<QStringList>();

	//Ҫ�򿪵�Ŀ¼
	QString dirPath;

	//�򿪵�ǰ·�����ߵ�ǰ�ļ�
	if(filePath.isNull()){
		dirPath = recentPaths.length() > 0 ? recentPaths.first() : "";
	}else if(info.isDir()){
        dirPath = info.absoluteFilePath();
		filePath.clear();
	}

	//����û�ѡ����ļ�·��
	if(filePath.isEmpty()){
		filePath = QFileDialog::getOpenFileName(this, tr("Open File"), dirPath, extFilters);
	}

	if(filePath.isNull()){
		return;
	}

	//���ļ�
	if(file->isOpen()){
		file->close();
	}
	file->setFileName(filePath);
	file->open(QFile::ReadWrite);

	//��ʾ�ļ�����
	ui->plainTextEdit->setPlainText(QString::fromLocal8Bit(file->readAll()));
	ui->plainTextEdit->moveCursor(QTextCursor::Start);

	//������ʷ��¼
	saveHistory();
}

void StylerWindow::on_actionSave_triggered(){
	QByteArray code = ui->plainTextEdit->toPlainText().toLocal8Bit();
	if(file->isOpen()){
		file->write(code);
	}else{
		QString dirPath = setting->value("styler/lastSavePath").toString();
		QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), dirPath);

		file->setFileName(filePath);
		file->open(QFile::ReadWrite);
		file->write(code);
	}

	//������ʷ��¼
	saveHistory();
}

void StylerWindow::on_actionSettings_triggered()
{
	SettingDialog *dialog = SettingDialog::getInstance();
	dialog->show();
}

void StylerWindow::on_actionExit_triggered()
{
	this->hide();
	ui->plainTextEdit->clear();
	file->close();
}

Action::Action(QWidget *parent):QWidgetAction(parent){

}

Action::Action(QString text, QWidget *parent):QWidgetAction(parent){
	this->setText(text);
}

void Action::triggerWithText(){
	emit triggered(this->text());
}

void StylerWindow::on_actionLockToolBar_triggered(bool checked){
	ui->toolBar->setMovable(!checked);
	setting->setValue("styler/toolBarLocked", checked);
}

void StylerWindow::on_actionFullScreen_triggered(){
	if(this->windowState() != Qt::WindowFullScreen){
		setWindowState(Qt::WindowFullScreen);
	}else{
		setWindowState(Qt::WindowNoState);
	}
}

void StylerWindow::saveHistory(){
	if(file->fileName().isEmpty()){
		return;
	}

	setting->beginGroup("styler");

	QFileInfo info(file->fileName());

	//���汾��Ŀ¼·��
	QString dirPath = info.absolutePath();
#ifdef Q_WS_WIN
	dirPath = dirPath.replace("/", "\\");
#endif

	QStringList recentPaths = setting->value("recentPaths").value<QStringList>();
	if(recentPaths.back() != dirPath){
		recentPaths.removeOne(dirPath);
		recentPaths.prepend(dirPath);

		while(recentPaths.length() > 5){
			recentPaths.removeLast();
		}

		setting->setValue("recentPaths", QVariant::fromValue(recentPaths));
	}

	//���汾���ļ�·��
	QString filePath = info.absoluteFilePath();
#ifdef Q_WS_WIN
	filePath = filePath.replace("/", "\\");
#endif
	QStringList recentFiles = setting->value("recentFiles").value<QStringList>();
	if(recentFiles.back() != filePath){
		recentFiles.removeOne(filePath);
		recentFiles.prepend(filePath);

		while(recentFiles.length() > 10){
			recentFiles.removeLast();
		}

		setting->setValue("recentFiles", QVariant::fromValue(recentFiles));
	}

	setting->endGroup();
}

void StylerWindow::on_actionToHTML_triggered(){

}
