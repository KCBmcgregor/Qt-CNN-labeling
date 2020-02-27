#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>
#include <QMenu>
#include <view.h>

class Image;

class PolygonItem : public QGraphicsPolygonItem
{
    QMenu rightClickMenu;


public:
    PolygonItem(QPolygonF polygonPoints, Image *parent = nullptr);
    using QGraphicsPolygonItem::boundingRect;
    using QGraphicsPolygonItem::paint;

    void requestCopyPasteSelectedShapes();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);



signals:

};

#endif // POLYGONITEM_H
