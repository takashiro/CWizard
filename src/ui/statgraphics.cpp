#include "statgraphics.h"

StatGraphics::StatGraphics(QObject *parent) :
	QGraphicsScene(parent),
	item_width(40),
	item_height(140)
{
	g.setStart(0, 0);
	g.setFinalStop(item_width * 1.5, 0);
	g.setColorAt(0, Qt::white);
	g.setColorAt(1, QColor(0x29,0xBD, 0xDF));
	g.setSpread(QGradient::RepeatSpread);
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

	QGraphicsRectItem *item;
	QGraphicsSimpleTextItem *text;

	i.toFront();
	while(i.hasNext()){
		i.next();

		height = (float) item_height / maxHeight * i.value();
		item = addRect(x, -height, item_width, height);
		item->setBrush(QBrush(g));

		text = addSimpleText(i.key());
		text->setPos(x - 5, 10 - item->y());

		text = addSimpleText(QString("%1").arg(i.value()) + tr("time(s)"));
		text->setPos(x - 5, 23 - item->y());

		x += item_width + 50;
	}
}
