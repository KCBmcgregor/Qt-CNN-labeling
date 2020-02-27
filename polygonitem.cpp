#include "polygonitem.h"
#include "image.h"
#include <QGraphicsSceneMouseEvent>


PolygonItem::PolygonItem(QPolygonF polygonPoints, Image *parent)
    : QGraphicsPolygonItem(polygonPoints, parent)
{
    //rightClickMenu.addAction("Copy", this, SLOT(requestCopyPasteSelectedShapes()));
    //rightClickMenu.addAction("Delete", this, SLOT());
    //rightClickMenu.addAction("Edit", this, SLOT());
}

void PolygonItem::requestCopyPasteSelectedShapes()
{
    ;
}

void PolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton)
        {
            rightClickMenu.exec((event->screenPos()));
        }
    QGraphicsPolygonItem::mousePressEvent(event);
}
