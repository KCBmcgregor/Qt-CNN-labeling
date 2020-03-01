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

    //! A public function
    /*!
     * Aquires the shapes from polygonitem
     */
    std::vector<PolygonItem * > getShapes() {return shapes;}

    //! A public function
    /*!
     * Adds a point to the shape
     * \param mousePos
     *
     */

    bool addPoint(QPointF mousePos);
    //! A public function
    /*!
     * Adds a line to the shape based off two points.
     * \param point1
     * \param point2
     *
     */
    bool addLine(QPointF point1, QPointF point2);
    //! A public function
    /*! Adds a shape to the image and sizes it dependent on the mode
      * \param shapePoints
      */

    bool addShape(QPolygonF shapePoints);
    //! A public function
    /*!
     * Deletes a shape from the image
     * \param shapeToDelete
     *
     */
    bool deleteShape(PolygonItem *shapeToDelete);

    //! A public function
    /*!
     * Draws a shape based off an existing one, copying their attributes.
     */
    bool addDrawnShape();
    //! A public function
    /*!
     * Copy and pastes a shape by taking its position and points to recreate the shape with a designated offset as to prevent perfect overlap.
     * \param shapes
     */
    void copyPasteShapes(std::vector<PolygonItem * > shapes);
    //!A public function
    /*!
     * Will copy the current attributes and increase/decrease the values depending on the mode, it will then delete the old shape and draw a new one.
     * \param selectedShapes
     */
    void shapeToResize(std::vector<PolygonItem * > selectedShapes);

    //!A public function
    /*!
     * Maps the adress of the selected shape.
     *
     */
    std::vector<PolygonItem * > findSelectedShapes();
    //!A public function
    /*!
     * Takes the position of the previous point and the current one and connects them with a line.
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
    //!A protected function
    /*!
     * Recognizes the left mouse click button when pressed and initializes the event to draw a point.
     * \param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // IMAGE_H
