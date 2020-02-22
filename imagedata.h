#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>


class ImageData
{
    QGraphicsPixmapItem *imagePt;
    int noOfShapes;
    //std::vector<QGraphicsPolygonItem> Shapes;

public:
    ImageData() {;}
    ImageData(QString imagePath);

    QGraphicsPixmapItem * getImagePt() {return imagePt;}
    int getNoOfShapes() {return noOfShapes;}
    //std::vector<QGraphicsPolygonItem> getShapes() {return Shapes;}

    ~ImageData();
};

#endif // IMAGEDATA_H

