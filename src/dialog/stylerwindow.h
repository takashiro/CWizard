#ifndef STYLERWINDOW_H
#define STYLERWINDOW_H

/* CStylerС���ߵĴ����� */

#include <QMainWindow>
#include <QEvent>

#include <QFileDialog>

class Styler;

namespace Ui {
    class StylerWindow;
}

class StylerWindow : public QMainWindow
{
    Q_OBJECT
	Styler *styler;

public:
	explicit StylerWindow(QWidget *parent = 0);
	~StylerWindow();
	static StylerWindow *getInstance(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);

private:
	Ui::StylerWindow *ui;
	QFile *file;						//��ǰ�򿪵��ļ�
	static const QString extFilters;	//������չ��


private slots:
	void on_actionOpen_triggered();		//��
	void on_actionCompress_triggered(); //ѹ��
	void on_actionFormat_triggered();	//�淶��
};

#endif // STYLERWINDOW_H
