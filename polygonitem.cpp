#include "polygonitem.h"
#include "image.h"
#include <QGraphicsSceneMouseEvent>

PolygonItem::PolygonItem(QPolygonF polygonPoints, Image *parentImage, QObject *parent)
    : QObject(parent),
      QGraphicsPolygonItem(polygonPoints, parentImage)
{
    rightClickMenu.addAction("Copy", parentImage, SLOT(copyPasteSelectedShapes()));
    rightClickMenu.addAction("Delete", parentImage, SLOT(deleteSelectedShapes()));
    rightClickMenu.addAction("Grow", parentImage, SLOT(growSelectedShapes()));
    rightClickMenu.addAction("Shrink", parentImage, SLOT(shrinkSelectedShapes()));

}


void PolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton)
        {
            rightClickMenu.exec((event->screenPos()));
        }
    QGraphicsPolygonItem::mousePressEvent(event);    
}



