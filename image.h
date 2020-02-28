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

/*!
 \hello im am a breife image discription

*/
class Image : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    QPointF mousePos; /*!< TODO: describe */
    std::vector<PolygonItem * > shapes; /*!< TODO: describe */
    std::vector<QGraphicsLineItem * > lines; /*!< TODO: describe */
    std::vector<QGraphicsEllipseItem * > points; /*!< TODO: describe */
    Model *model; /*!< TODO: describe */
    QMap<std::string, QPen> pens; /*!< TODO: describe */

public:
    /*!
     \brief

     \param imagePath
     \param model
     \param parent
    */
    explicit Image(QString imagePath, Model *model, QObject *parent = nullptr);
    using QGraphicsPixmapItem::boundingRect;
    using QGraphicsPixmapItem::paint;

    /*!
     \brief

     \return std::vector<PolygonItem *>
    */
    std::vector<PolygonItem * > getShapes() {return shapes;}

    /*!
     \brief

     \param mousePos
     \return bool
    */
    bool addPoint(QPointF mousePos);
    /*!
     \brief

     \param point1
     \param point2
     \return bool
    */
    bool addLine(QPointF point1, QPointF point2);
    /*!
     \brief

     \param shapePoints
     \return bool
    */
    bool addShape(QPolygonF shapePoints);
    /*!
     \brief

     \param shapeToDelete
     \return bool
    */
    bool deleteShape(PolygonItem *shapeToDelete);
    /*!
     \brief

     \return bool
    */
    bool addDrawnShape();

    /*!
     \brief

     \param shapes
    */
    void copyPasteShapes(std::vector<PolygonItem * > shapes);
    /*!
     \brief

     \param selectedShapes
    */
    void shapeToResize(std::vector<PolygonItem * > selectedShapes);

    /*!
     \brief

     \return std::vector<PolygonItem *>
    */
    std::vector<PolygonItem * > findSelectedShapes();

    /*!
     \brief

     \return bool
    */
    bool connectLastDrawnPoints();

    //bool moveVertex(Image *parent, QPolygonF shapePoints, QPointF mousePos);

public slots:
    /*!
     \brief

    */
    void copyPasteSelectedShapes();
    /*!
     \brief

    */
    void deleteSelectedShapes();

protected:
    /*!
     \brief

     \param event
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // IMAGE_H
