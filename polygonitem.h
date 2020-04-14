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

class Point;

class Image;

class PolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

    Image *parentImage = nullptr;
    std::pair<QString,int> classifier = {"",-1};
    QGraphicsSimpleTextItem *classifierText;

    QMenu rightClickMenu;
    QAction *edit;
    QAction *modify;


public:
    explicit PolygonItem(QPolygonF polygonPoints, Image *parentImage = nullptr, QObject *parent = nullptr);
    using QGraphicsPolygonItem::boundingRect;
    using QGraphicsPolygonItem::paint;

    void requestCopyPasteSelectedShapes();
    void centerText();
    void writeShapeData(QTextStream *write);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void assignClassifier(QString c, int lineIndex);
    QString getClassifier();
    int getLineIndex();
    void startModifying();
    void updatePolygonPointPosition(int pointIndex, QPointF newPos);
    void stopModifying();


signals:

};

#endif // POLYGONITEM_H
