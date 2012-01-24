#ifndef TRAY_H
#define TRAY_H

#include <QEvent>
#include <QMouseEvent>

#include "cwizard.h"

class Tray: public QObject
{
public:
	CWizard *cwizard;

	Tray(CWizard *cwizard);

	bool eventFilter(QObject *obj, QEvent *event);
};

#endif // TRAY_H
