#include "statgraphics.h"

StatGraphics::StatGraphics(QObject *parent) :
	QGraphicsScene(parent)
{

}

void StatGraphics::loadData(QString &data){
	QMap<QString, int> labels;
	foreach(const QString &label, data.split(" ", QString::SkipEmptyParts)){
		QStringList tmp = label.split(' ');
		labels[tmp.at(0)] = tmp.at(1).toInt();
	}

	setLabels(labels);
}

void StatGraphics::loadFile(QFile &file){
	QString data(file.readAll());
	loadData(data);
}


void StatGraphics::setLabels(QMap<QString, int> &labels){
	clear();

	const int width = 40;
	int x = 0;
	int maxHeight = 1;
	int height;

	QMapIterator<QString, int> i(labels);
	while(i.hasNext()){
		i.next();

		if(i.value() > maxHeight){
			maxHeight = i.value();
		}
	}

	i.toFront();
	while(i.hasNext()){
		i.next();

		height = 40.0 / maxHeight * i.value();
		QGraphicsRectItem *item = addRect(x, -height, width, height);
		QGraphicsSimpleTextItem *text = addSimpleText(i.key());
		text->setPos(x - 5, 10 - item->y());
		QGraphicsSimpleTextItem *number = addSimpleText(QString("%1").arg(i.value()) + tr("time(s)"));
		number->setPos(x - 5, 23 - item->y());

		x += width + 50;
	}
}
