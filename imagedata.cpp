#include "imagedata.h"
#include <QGraphicsTextItem>
#include <QPainterPath>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <model.h>
#include <view.h>


ImageData::ImageData(QString imagePath, Model * m)
{
    imagePt = new Image(imagePath, m, this);
    noOfShapes = 0;
    shapes = {};
    model = m;
    pens = model->requestPens();
}

bool ImageData::addPoint(Image *parent, QPointF mousePos)
{
    qreal x = mousePos.x();
    qreal y = mousePos.y();
    QGraphicsEllipseItem *shape =  new QGraphicsEllipseItem(0,0,10,10,parent);
    shape->setPos(x,y);
    shape->setPen(pens["pointPen"]);
    points.push_back(shape);
    return true;
}

bool ImageData::addLine(Image *parent, QPointF point1, QPointF point2)
{
    QGraphicsLineItem *line = new QGraphicsLineItem(point1.x(), point1.y(),
                                                     point2.x(), point2.y(),
                                                     parent);
    line->setPen(pens["linePen"]);
    lines.push_back(line);
    return true;
}


/*bool ImageData::copyPaste(){
    addDrawnShape();
    return true;
}*/

bool ImageData::addShape(Image *parent, QPolygonF shapePoints)
{
    QGraphicsPolygonItem *shape = new QGraphicsPolygonItem(shapePoints, parent);
    shape->setFlag(QGraphicsPolygonItem::ItemIsMovable);
    shape->setFlag(QGraphicsPolygonItem::ItemIsSelectable);
    //shape->setFlag(QGraphicsPolygonItem::ItemSendsGeometryChanges);
    //shape->setFlag(QGraphicsPolygonItem::ItemIsFocusable);

    shape->setPen(pens["shapePen"]);
    shapes.push_back(shape);
    return true;
}

bool ImageData::addDrawnShape()
{
    std::string mode2 = model->requestMode2();
    QPolygonF shapePoints = {};
    for(unsigned i=0; i < points.size(); i++) {
        QPointF nextPoint = points[i]->pos();
        shapePoints.append(nextPoint);
    }

    addShape(imagePt, shapePoints);

    if (mode2=="copy"){
        addShape(imagePt, shapePoints);
    }




    for(unsigned i=0; i < points.size(); i++) {
        points[i]->setParentItem(NULL);
        delete points[i];
    }
    for(unsigned i=0; i < lines.size(); i++) {
        lines[i]->setParentItem(NULL);
        delete lines[i];
    }



    return true;
}



bool ImageData::connectLastDrawnPoints()
{
    QGraphicsEllipseItem * lastDrawnPoint = points[points.size() - 1];
    QGraphicsEllipseItem * secondToLastDrawnPoint = points[points.size() - 2];
    QPointF lastDrawnPosition = secondToLastDrawnPoint->pos();
    QPointF secondTolastDrawnPosition = lastDrawnPoint->pos();
    //QPointF secondTolastDrawnPositionM = secondToLastDrawnPoint->mapFromParent(0,0);
    //QPointF lastDrawnPositionM = lastDrawnPoint->mapFromParent(0,0);

    addLine(imagePt, lastDrawnPosition, secondTolastDrawnPosition);
    return true;
}


ImageData::~ImageData()
{
    delete this;
}


Image::Image(QString path,Model *m, ImageData *iD):QGraphicsPixmapItem(path)
{
    imageData = iD;
    model = m;
}

void Image::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    mousePos = (event->scenePos());
    std::string mode = model->requestMode();
    if (mode == "draw")
    {
        if(imageData->addPoint(this, mousePos))
        {
            model->pointDrawn();
        }
    }

    update();
    QGraphicsPixmapItem::mousePressEvent(event);
}




void Image::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    mousePos = (event->pos());
    update();
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void Image::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
