#ifndef WRITINGHABIT_H
#define WRITINGHABIT_H

#include <QString>

struct WritingHabit{
	int bioperator;
	int comma;
	int brace;

	int total;

	WritingHabit();

	WritingHabit &operator += (const WritingHabit &plus);

	QString toString() const;
	static WritingHabit fromString(QString str);
};

#endif // WRITINGHABIT_H
