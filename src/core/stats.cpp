#include "stats.h"

Stats *stats = NULL;

Stats::Stats(){
	stats = this;
}

void Stats::updateTodayLog(QString date, WritingHabit &value){
	//data[date] = value;
}

bool Stats::uploadLogs() const{
	return false;
}

QMap<QString, WritingHabit> Stats::getLogs(int days) const{
    return QMap<QString, WritingHabit>();
}

WritingHabit Stats::getLog(QString date) const{
	return data.value(date);
}
