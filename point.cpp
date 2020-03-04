#include "point.h"
#include "polygonitem.h"
#include "image.h"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


Point::Point(qreal x, qreal y, qreal width, qreal height, Image *parent)
    : QObject(parent),
      QGraphicsEllipseItem(x, y, width, height, parent)
{
    polygonIndex = -1;
}

Point::Point(qreal x, qreal y, qreal width, qreal height, int pI, PolygonItem *parent)
    : QObject(parent),
      QGraphicsEllipseItem(x, y, width, height, parent)
{
    polygonIndex = pI;
    setFlag(Point::ItemIsMovable);
    setFlag(Point::ItemIsSelectable);

    QObject::connect(this, &Point::positionChanged,
                         parent, &PolygonItem::updatePolygonPointPosition);
}

void Point::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = (event->scenePos());
    setPos(pos);
    emit positionChanged(polygonIndex, pos);
    update();
}
