#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <string>
#include <map>
#include <vector>

struct Point
{
    int x;
    int y;
};

class Shape
{
    std::string shapeType;
    std::vector<Point> Points;
    std::string annotation;
    bool showingAnnotation;
public:
    Shape();

};

class ImageData
{
    std::string name;
    int noOfShapes;
    int noOfAnnoation;
    std::vector<Shape> Shapes;

public:
    ImageData();
    ~ImageData();
};

#endif // IMAGEDATA_H

