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
 \brief The image object is a custom QGraphicsPixmapItem
 for diplaying to the scene along with all its child Items.
*/
class Image : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    QPointF mousePos; /*!< Holds the position of the mouse coursor within the image. */
    std::vector<PolygonItem * > shapes; /*!< Holds the adresses of the shapes (PolygonItems) that are on the image. */
    std::vector<QGraphicsLineItem * > lines; /*!< Holds the adresses of the lines (QGraphicsLineItem) that are on the image. */
    std::vector<QGraphicsEllipseItem * > points; /*!< Holds the adresses of the points (QGraphicsEllipseItem) that are on the image. */
    Model *model; /*!< a pointer to the Model object for calling its methods. */
    QMap<std::string, QPen> pens; /*!< A QMap holding QPens that are used to draw points, line and shapes. */

public:
    /*!
     \brief Image object constructor to be instantiated with the new keyword.

     \param imagePath A file path to a compatible image that will be loaded as the QGraphicsPixmapItem.
     \param model A pointer to the Model object for refernce.
     \param parent leave as nullptr.
    */
    explicit Image(QString imagePath, Model *model, QObject *parent = nullptr);

    using QGraphicsPixmapItem::boundingRect;
    using QGraphicsPixmapItem::paint;

    /*!
     \brief accsess method

     \return std::vector<PolygonItem *> member variable
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
