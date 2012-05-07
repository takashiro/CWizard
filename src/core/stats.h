#ifndef STATS_H
#define STATS_H

#include "structs.h"
#include "writinghabit.h"

#include <QString>
#include <QMap>
#include <QObject>

class Stats: public QObject{
	Q_OBJECT

public:
	Stats();	//��ʼ��ʱĬ�ϼ��ؽ��ռ�¼
	~Stats();
	static Stats *getInstance();

	void updateTodayLog(WritingHabit &value);			//���½��ռ�¼������Ϊ�仯��
	void updateLog(QString date, WritingHabit &plus);	//����date(ISO��׼��ʽyyyy-mm-dd)�����µļ�¼��plusΪ�仯��
	bool uploadLogs() const;							//����¼�ϴ���������

	QMap<QString, WritingHabit> getLogs() const;		//��õ�ǰ���ص�ȫ����¼
	WritingHabit getLog(QString date);					//���date(ISO��׼��ʽyyyy-mm-dd)�����µļ�¼
	WritingHabit getTodayLog() const;					//��ý��ռ�¼

	bool loadData(QString date);						//����date(ISO��׼��ʽyyyy-mm-dd)���ڵļ�¼������ʧ�ܷ���false

public slots:
	void updateTodayLog(HabitType type);				//���½��ռ�¼�µ�����һ�������������1��

private:
	QMap<QString, WritingHabit> data;					//�洢��ǰ���ص��ڴ��ȫ������
	WritingHabit *today;								//ָ�������ݵ�ָ��
};

extern Stats *stats;

#endif // STATS_H
