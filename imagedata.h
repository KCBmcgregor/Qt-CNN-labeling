#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>
#include <view.h>



class Model;
class ImageData;

class Image :public QGraphicsPixmapItem
{
    Model *model;
    ImageData *imageData;
public:
    bool pressed = false;
    Image(QString path, Model *model, ImageData *imageData);
    using QGraphicsPixmapItem::boundingRect;
    using QGraphicsPixmapItem::paint;

    QPointF mousePos;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class ImageData
{
    Image *imagePt;
    int noOfShapes;
    std::vector<QGraphicsPolygonItem * > shapes;
    std::vector<QGraphicsLineItem * > lines;
    std::vector<QGraphicsEllipseItem * > points;
    Model *model;
    QMap<std::string, QPen> pens;





public:
    ImageData() {;}
    ImageData(QString imagePath, Model *model);

    QGraphicsPixmapItem * getImagePt() {return imagePt;}
    int getNoOfShapes() {return noOfShapes;}
    std::vector<QGraphicsPolygonItem * > getShapes() {return shapes;}

    bool addPoint(Image *parent, QPointF mousePos);
    bool addLine();

    bool addShape();


    ~ImageData();
};

#endif // IMAGEDATA_H

