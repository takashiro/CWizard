#include "stats.h"

#include <QFile>
#include <QDate>

Stats *stats = NULL;

Stats::Stats(){
	stats = this;

	QString date = QDate::currentDate().toString(Qt::ISODate);
	QFile file("./log/" + date + ".dat");
	file.open(QFile::ReadOnly);
	data[date] = WritingHabit::fromString(QString::fromLocal8Bit(file.readAll()));
	file.close();

	today = &data[date];
}

Stats::~Stats(){
	QFile file;

	QMapIterator<QString, WritingHabit> iter(data);
	while(iter.hasNext()){
		iter.next();

		file.setFileName("./log/" + iter.key() + ".dat");
		file.open(QFile::WriteOnly);
		file.write(iter.value().toString().toLocal8Bit());
		file.close();
	}
}

Stats *Stats::getInstance(){
	static Stats *instance = new Stats();
	return instance;
}

void Stats::updateTodayLog(WritingHabit &value){

}

void Stats::updateTodayLog(HabitType type){
	switch(type){
	case Bioperator:
		today->bioperator++;
		break;

	case Comma:
		today->comma++;
		break;

	case Brace:
		today->brace++;
		break;

	default:;
	}

	today->total++;
}

void Stats::updateLog(QString date, WritingHabit &plus){
	data[date] += plus;
}

bool Stats::uploadLogs() const{
	return false;
}

QMap<QString, WritingHabit> Stats::getLogs() const{
	return data;
}

WritingHabit Stats::getLog(QString date) const{
	return data.value(date);
}
