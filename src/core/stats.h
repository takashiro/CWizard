#ifndef STATS_H
#define STATS_H

#include "structs.h"

#include <QString>
#include <QMap>

class Stats
{
public:
    Stats();

	void updateTodayLog(QString date, WritingHabit &value);
	bool uploadLogs() const;

	QMap<QString, WritingHabit> getLogs(int days) const;
	WritingHabit getLog(QString date) const;

private:
	QMap<QString, WritingHabit> data;
};

#endif // STATS_H
