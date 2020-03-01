#include "polygonitem.h"
#include "image.h"
#include <QGraphicsSceneMouseEvent>

PolygonItem::PolygonItem(QPolygonF polygonPoints, Image *pI, QObject *parent)
    : QObject(parent),
      QGraphicsPolygonItem(polygonPoints, pI)
{
    parentImage = pI;

    rightClickMenu.addAction("Copy", parentImage, SLOT(copyPasteSelectedShapes()));
    edit = rightClickMenu.addAction("Edit", this, SLOT(startModifying()));
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

void PolygonItem::startModifying()
{
    QPolygonF polygonPoints = polygon();
    for (int i = 0; i < polygonPoints.size(); i++)
    {
        parentImage->addPoint(polygonPoints[i],i , this);
    }
    rightClickMenu.removeAction(edit);
    modify = rightClickMenu.addAction("Complete Edit", this, SLOT(stopModifying()));
}

void PolygonItem::updatePolygonPointPosition(int pointIndex, QPointF newPos)
{
    QPolygonF newPolygon = polygon();
    newPolygon[pointIndex] = newPos;
    setPolygon(newPolygon);
    update();
    parentImage->update();
}

void PolygonItem::stopModifying()
{
    QList<QGraphicsItem * > points = childItems();
    foreach(QGraphicsItem *point, points)
    {
        delete point;
    }
    rightClickMenu.removeAction(modify);
    edit = rightClickMenu.addAction("Edit", this, SLOT(startModifying()));
}



