#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <QObject>
#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>
#include <QMenu>
#include <view.h>
#include <QPainter>

class Image;

class PolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

    QMenu rightClickMenu;
public:
    explicit PolygonItem(QPolygonF polygonPoints, Image *parentImage = nullptr, QObject *parent = nullptr);
    using QGraphicsPolygonItem::boundingRect;
    using QGraphicsPolygonItem::paint;

    void requestCopyPasteSelectedShapes();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool Pressed;

signals:

};

#endif // POLYGONITEM_H
