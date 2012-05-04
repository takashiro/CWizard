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
	Stats();
	~Stats();
	static Stats *getInstance();

	void updateTodayLog(WritingHabit &value);
	void updateLog(QString date, WritingHabit &plus);
	bool uploadLogs() const;

	QMap<QString, WritingHabit> getLogs() const;
	WritingHabit getLog(QString date);
	WritingHabit getTodayLog() const;

	bool loadData(QString date);

public slots:
	void updateTodayLog(HabitType type);

private:
	QMap<QString, WritingHabit> data;
	WritingHabit *today;
};

extern Stats *stats;

#endif // STATS_H
