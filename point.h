#ifndef POINT_H
#define POINT_H

#include "polygonitem.h"
#include "image.h"
#include <QObject>
#include <QGraphicsItem>

class Point : public QObject,  public QGraphicsEllipseItem
{
    Q_OBJECT

    int polygonIndex;
public:
    explicit Point() {;}
    explicit Point(qreal x, qreal y, qreal width, qreal height, Image *parent = nullptr);
    explicit Point(qreal x, qreal y, qreal width, qreal height, int pI , PolygonItem *parent = nullptr);
    using QGraphicsEllipseItem::boundingRect;
    using QGraphicsEllipseItem::paint;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void positionChanged(int polygonIndex, QPointF pos);

};

#endif // POINT_H
