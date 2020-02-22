#include "imagedata.h"

ImageData::ImageData(QString imagePath)
{
    imagePt = new QGraphicsPixmapItem(imagePath);;
    noOfShapes = 0;
    //Shapes = {};
}

ImageData::~ImageData()
{
    delete this;
}



