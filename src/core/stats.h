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
	Stats();	//初始化时默认加载今日记录
	~Stats();
	static Stats *getInstance();

	void updateTodayLog(WritingHabit &value);			//更新今日记录，参数为变化量
	void updateLog(QString date, WritingHabit &plus);	//更新date(ISO标准格式yyyy-mm-dd)日期下的记录，plus为变化量
	bool uploadLogs() const;							//将记录上传到服务器

	QMap<QString, WritingHabit> getLogs() const;		//获得当前加载的全部记录
	WritingHabit getLog(QString date);					//获得date(ISO标准格式yyyy-mm-dd)日期下的记录
	WritingHabit getTodayLog() const;					//获得今日记录

	bool loadData(QString date);						//加载date(ISO标准格式yyyy-mm-dd)日期的记录，加载失败返回false

public slots:
	void updateTodayLog(HabitType type);				//更新今日记录下的其中一项（该项数量自增1）

private:
	QMap<QString, WritingHabit> data;					//存储当前加载到内存的全部数据
	WritingHabit *today;								//指向当日数据的指针
};

extern Stats *stats;

#endif // STATS_H
