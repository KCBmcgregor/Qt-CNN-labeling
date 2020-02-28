#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>
#include <QMenu>
#include <view.h>
#include <polygonitem.h>

class Image : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    QPointF mousePos;
    std::vector<PolygonItem * > shapes;
    std::vector<QGraphicsLineItem * > lines;
    std::vector<QGraphicsEllipseItem * > points;
    Model *model;
    QMap<std::string, QPen> pens;

public:
    explicit Image(QString imagePath, Model *model, QObject *parent = nullptr);
    using QGraphicsPixmapItem::boundingRect;
    using QGraphicsPixmapItem::paint;

    std::vector<PolygonItem * > getShapes() {return shapes;}

    bool addPoint(QPointF mousePos);
    bool addLine(QPointF point1, QPointF point2);
    bool addShape(QPolygonF shapePoints);
    bool deleteShape(PolygonItem *shapeToDelete);
    bool addDrawnShape();

    void copyPasteShapes(std::vector<PolygonItem * > shapes);
    void shapeToResize(std::vector<PolygonItem * > selectedShapes);

    std::vector<PolygonItem * > findSelectedShapes();

    bool connectLastDrawnPoints();

    //bool moveVertex(Image *parent, QPolygonF shapePoints, QPointF mousePos);

public slots:
    void copyPasteSelectedShapes();
    void deleteSelectedShapes();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // IMAGE_H
