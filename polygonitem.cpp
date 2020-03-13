#include "polygonitem.h"
#include "image.h"
#include "point.h"
#include <QGraphicsSceneMouseEvent>
#include <typeinfo>

PolygonItem::PolygonItem(QPolygonF polygonPoints, Image *pI, QObject *parent)
    : QObject(parent),
      QGraphicsPolygonItem(polygonPoints, pI)
{
    parentImage = pI;

    classifierText = new QGraphicsSimpleTextItem("", this);
    classifierText->setZValue(25);
    centerText();

    rightClickMenu.addAction("Copy", parentImage, SLOT(copyPasteSelectedShapes()));
    edit = rightClickMenu.addAction("Edit", this, SLOT(startModifying()));
    rightClickMenu.addAction("Delete", parentImage, SLOT(deleteSelectedShapes()));
    rightClickMenu.addAction("Grow", parentImage, SLOT(growSelectedShapes()));
    rightClickMenu.addAction("Shrink", parentImage, SLOT(shrinkSelectedShapes()));

}

void PolygonItem::centerText()
{
    QPointF shapeCenter = boundingRect().center();
    classifierText->setPos(shapeCenter);
}

void PolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton)
        {
            rightClickMenu.exec((event->screenPos()));
        }
    QGraphicsPolygonItem::mousePressEvent(event);
}

void PolygonItem::assignClassifier(QString c, int lineIndex)
{
    classifier = {c, lineIndex};
    classifierText->setText(c);

}

QString PolygonItem::getClassifier()
{
    QString c = classifierText->text();
    return c;
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
    centerText();
}

void PolygonItem::stopModifying()
{
    QList<QGraphicsItem * > points = childItems();
    foreach(QGraphicsItem *point, points)
    {
        if( typeid( *point ) == typeid( Point ) )
        {
           delete point;
        }
    }
    rightClickMenu.removeAction(modify);
    edit = rightClickMenu.addAction("Edit", this, SLOT(startModifying()));
}



