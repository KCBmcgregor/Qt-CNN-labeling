#include "image.h"
#include "polygonitem.h"
#include <QGraphicsTextItem>
#include <QPainterPath>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include<QtTest/QTest>
#include <view.h>
#include <model.h>


Image::Image(QString path, Model *m, QObject *parent) : QObject(parent), QGraphicsPixmapItem(path)
{
    model = m;
    points = {};
    lines = {};
    shapes = {};
    pens = model->requestPens();

}

bool Image::addPoint(QPointF mousePos)
{
    qreal x = mousePos.x();
    qreal y = mousePos.y();
    QGraphicsEllipseItem *shape =  new QGraphicsEllipseItem(0,0,10,10,this);
    shape->setPos(x,y);
    shape->setPen(pens["pointPen"]);
    points.push_back(shape);
    return true;
}

bool Image::addLine(QPointF point1, QPointF point2)
{
    QGraphicsLineItem *line = new QGraphicsLineItem(point1.x(), point1.y(),
                                                     point2.x(), point2.y(),
                                                  this);
    line->setPen(pens["linePen"]);
    lines.push_back(line);
    return true;
}

bool Image::addShape(QPolygonF shapePoints)
{

    PolygonItem *shape = new PolygonItem(shapePoints, this);
    shape->setFlag(PolygonItem::ItemIsMovable);
    shape->setFlag(PolygonItem::ItemIsSelectable);
    shape->setPen(pens["shapePen"]);
    shapes.push_back(shape);
    return true;
}

bool Image::deleteShape(PolygonItem *shapeToDelete)
{
    for(unsigned i=0; i < shapes.size(); i++)
    {
        if (shapes[i] == shapeToDelete)
        {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
            break;
        }

    }
    return true;
}
                                     //! If resize mode3 on 'shrink' or 'grow' resize function will execute.
void Image::growShape(PolygonItem *shapeToResize)
{
    QPolygonF shapePoints;
    shapePoints = shapeToResize->polygon();
    PolygonItem *shape = shapeToResize;
    shape->setTransformOriginPoint(shapePoints[0]);
    shape->setScale(1.2);
    //for(int i = 0; i < shapePoints.size(); i++)
    //{

    //}
    shape->setSelected(false);

}

void Image::shrinkShape(PolygonItem *shapeToResize)
{
    QPolygonF shapePoints;
    shapePoints = shapeToResize->polygon();
    PolygonItem *shape = shapeToResize;
    shape->setTransformOriginPoint(shapePoints[0]);
    shape->setScale(0.8);

}



bool Image::addDrawnShape()
{
    std::string mode2 = model->requestMode2();
    QPolygonF shapePoints = {};
    for(unsigned i=0; i < points.size(); i++) {
        QPointF nextPoint = points[i]->pos();
        shapePoints.append(nextPoint);
    }

    addShape(shapePoints);

    if (mode2=="copy"){                                 //! If mode2 set to copy, the a duplicate of the drawn shape is created
        addShape(shapePoints);
    }

    for(unsigned i=0; i < points.size(); i++) {
        points[i]->setParentItem(NULL);
        delete points[i];
    }
    points = {};

    for(unsigned i=0; i < lines.size(); i++) {
        lines[i]->setParentItem(NULL);
        delete lines[i];
    }
    lines = {};

    return true;
}

void Image::copyPasteShapes(std::vector<PolygonItem *> shapesToCopyPaste)
{
    qreal pasteOffset = 50;
    QPointF pos;
    QPolygonF shapePoints;

    for(unsigned i=0; i < shapesToCopyPaste.size(); i++)
    {
        shapesToCopyPaste[i]->setSelected(false);
        shapePoints = shapesToCopyPaste[i]->polygon();
        pos = shapesToCopyPaste[i]->pos();
        pos.setX(pos.x() + pasteOffset);
        pos.setY(pos.y() + pasteOffset);
        addShape(shapePoints);
        shapes.back()->setPos(pos);
        shapes.back()->setSelected(true);
    }
}

void Image::copyPasteSelectedShapes()
{
    copyPasteShapes(findSelectedShapes());
}

void Image::growSelectedShapes()
{
    std::vector<PolygonItem * > shapesToResize = findSelectedShapes();
    for(unsigned i=0; i < shapesToResize.size(); i++)
    {
        growShape(shapesToResize[i]);
    }

}

void Image::shrinkSelectedShapes()
{
    std::vector<PolygonItem * > shapesToResize = findSelectedShapes();
    for(unsigned i=0; i < shapesToResize.size(); i++)
    {
        shrinkShape(shapesToResize[i]);
    }

}


void Image::deleteSelectedShapes()
{
    std::vector<PolygonItem * > shapesToDelete = findSelectedShapes();
    for(unsigned i=0; i < shapesToDelete.size(); i++)
    {
        deleteShape(shapesToDelete[i]);
    }
}

std::vector<PolygonItem * > Image::findSelectedShapes()
{
    std::vector<PolygonItem * > selectedShapes = {};
    for(unsigned i=0; i < shapes.size(); i++)
    {
        if (shapes[i]->isSelected())
        {
            selectedShapes.push_back(shapes[i]);
        }
    }
    return selectedShapes;
}

bool Image::connectLastDrawnPoints()
{
    QGraphicsEllipseItem * lastDrawnPoint = points[points.size() - 1];
    QGraphicsEllipseItem * secondToLastDrawnPoint = points[points.size() - 2];
    QPointF lastDrawnPosition = secondToLastDrawnPoint->pos();
    QPointF secondTolastDrawnPosition = lastDrawnPoint->pos();

    addLine(lastDrawnPosition, secondTolastDrawnPosition);
    return true;
}

void Image::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   mousePos = (event->scenePos());

    if (event->buttons() == Qt::LeftButton)
    {
        std::string mode = model->requestMode();
        if (mode == "draw")
        {
            if(addPoint(mousePos))
            {
                model->pointDrawn();
            }
        }
        update();
    }
    QGraphicsPixmapItem::mousePressEvent(event);
}

