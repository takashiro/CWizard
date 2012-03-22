#include "stats.h"

Stats::Stats()
{
}

void Stats::updateTodayLog(QString date, WritingHabit &value){
	data[date] = value;
}

bool Stats::uploadLogs() const{
	return false;
}

QMap<QString, WritingHabit> Stats::getLogs(int days) const{

}

WritingHabit Stats::getLog(QString date) const{
	return data.value(date);
}
