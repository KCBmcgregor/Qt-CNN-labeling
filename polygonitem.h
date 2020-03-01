#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <QObject>
#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>
#include <QMenu>
#include <view.h>
#include <QPainter>

class Image;

/*!
 \brief

*/
class PolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

    QMenu rightClickMenu; /*!< TODO: describe */
public:
    //! A public constructor
    /*!
     * Creates the polygon shapes based off of given parameters.
     * \param polygonPoints
     * \param parentImage
     * \param parent
     */
    explicit PolygonItem(QPolygonF polygonPoints, Image *parentImage = nullptr, QObject *parent = nullptr);
    using QGraphicsPolygonItem::boundingRect;
    using QGraphicsPolygonItem::paint;


protected:
    //! A protected event function
    /*!
     * Used to determine right clicks on shapes to display the gui and pass the event onto the base  class.
     * \param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool Pressed; /*!< TODO: describe */

signals:

};

#endif // POLYGONITEM_H
