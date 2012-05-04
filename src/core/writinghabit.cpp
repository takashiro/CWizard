#include "writinghabit.h"

#include <QStringList>

WritingHabit::WritingHabit(){
	bioperator = comma = brace = total = 0;
}

WritingHabit &WritingHabit::operator+=(const WritingHabit &plus){
	this->bioperator += plus.bioperator;
	this->comma += plus.comma;

	this->total = this->bioperator + this->comma;

	return *this;
}

QString WritingHabit::toString() const{
	return QString("%1\t%2\t%3").arg(this->bioperator).arg(this->comma).arg(this->brace);
}

WritingHabit WritingHabit::fromString(QString str){
	QStringList strlist = str.split("\t");

	WritingHabit habit;
	if(!str.isEmpty()){
		habit.bioperator = strlist.at(0).toInt();
		habit.comma = strlist.at(1).toInt();

		habit.total = habit.bioperator + habit.comma;
	}

	return habit;
}
