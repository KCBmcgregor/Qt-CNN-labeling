#include "imagedata.h"
#include <QGraphicsTextItem>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <model.h>


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
    QGraphicsEllipseItem *shape =  new QGraphicsEllipseItem(x,y,10,10,parent);
    shape->setPen(pens["pointPen"]);
    points.push_back(shape);
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
        imageData->addPoint(this, mousePos);
    }
    update();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Image::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    mousePos = (event->scenePos());
    update();
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void Image::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
