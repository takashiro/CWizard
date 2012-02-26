#ifndef STYLERWINDOW_H
#define STYLERWINDOW_H

/* CStylerС���ߵĴ����� */

#include <QMainWindow>
#include <QEvent>
#include <QFileDialog>
#include <QSettings>
#include <QWidgetAction>

class Styler;

namespace Ui {
    class StylerWindow;
}

class StylerWindow : public QMainWindow
{
    Q_OBJECT
private:
	Ui::StylerWindow *ui;
	QFile *file;						//��ǰ�򿪵��ļ�
    static const QString extFilters;	//������չ��
	QSettings *setting;					//������Ϣ

	Styler *styler;

public:
	explicit StylerWindow(QWidget *parent = 0);
	~StylerWindow();
	static StylerWindow *getInstance(QWidget *parent = 0);

public slots:
	void openFile(QString filePath = QString());		//���ļ�
	void saveHistory();									//������ʷ��¼

private slots:
	void on_actionSettings_triggered();
	void on_actionOpen_triggered();						//���ļ�
	void on_actionSave_triggered();						//�����ļ�
	void on_actionCompress_triggered();					//ѹ��
	void on_actionFormat_triggered();					//�淶��
	void on_actionLockToolBar_triggered(bool checked);
	void on_actionFullScreen_triggered();
	void on_actionExit_triggered();
    void on_actionToHTML_triggered();
};

class Action: public QWidgetAction{
	Q_OBJECT

public:
	explicit Action(QWidget *parent = 0);
	Action(QString text, QWidget *parent = 0);

public slots:
	void triggerWithText();

signals:
	void triggered(QString text);
};

#endif // STYLERWINDOW_H
