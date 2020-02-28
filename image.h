#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>
#include <QMenu>
#include <view.h>
#include <polygonitem.h>

class Model;

class Image : public QGraphicsPixmapItem
{
    QPointF mousePos;
    std::vector<PolygonItem * > shapes;
    std::vector<QGraphicsLineItem * > lines;
    std::vector<QGraphicsEllipseItem * > points;
    Model *model;
    QMap<std::string, QPen> pens;



public:
    Image() {;}
    Image(QString imagePath, Model *model);
    using QGraphicsPixmapItem::boundingRect;
    using QGraphicsPixmapItem::paint;

    std::vector<PolygonItem * > getShapes() {return shapes;}

    bool addPoint(QPointF mousePos);
    bool addLine(QPointF point1, QPointF point2);
    bool addShape(QPolygonF shapePoints);
    bool addDrawnShape();

    void copyPasteShapes(std::vector<PolygonItem * > shapes);
    void shapeToResize(std::vector<PolygonItem * > selectedShapes);
    void copyPasteSelectedShapes();
    std::vector<PolygonItem * > findSelectedShapes();

    bool connectLastDrawnPoints();

    //bool moveVertex(Image *parent, QPolygonF shapePoints, QPointF mousePos);

    ~Image();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


};

#endif // IMAGE_H
