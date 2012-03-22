#ifndef STATGRAPHICS_H
#define STATGRAPHICS_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSettings>
#include <QFile>
#include <QMap>

class StatGraphics : public QGraphicsScene
{
    Q_OBJECT
public:
	explicit StatGraphics(QObject *parent = 0);

	void loadData(QString &data);
	void loadFile(QFile &file);

	void setLabels(QMap<QString, int> &labels);
};

#endif // STATGRAPHICS_H
