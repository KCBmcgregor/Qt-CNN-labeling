#include "image.h"
#include "point.h"
#include "polygonitem.h"
#include <QGraphicsTextItem>
#include <QPainterPath>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
//#include<QtTest/QTest>
#include <view.h>
#include <model.h>
#include <control.h> //to be commented out



Image::Image(QString path, Model *m, QObject *parent) : QObject(parent), QGraphicsPixmapItem(path)
{
    model = m;
    points = {};
    lines = {};
    shapes = {};

    QPen pointPen(Qt::red);
    pens["pointPen"] = pointPen;

    QPen linePen(Qt::black);
    linePen.setWidth(6);
    linePen.setJoinStyle(Qt::MiterJoin);
    pens["linePen"] = linePen;

    QPen shapePen(Qt::green);
    shapePen.setWidth(6);
    shapePen.setJoinStyle(Qt::MiterJoin);
    pens["shapePen"] = shapePen;

    QBrush pointBrush(Qt::red,Qt::SolidPattern);
    brushes["pointBrush"] = pointBrush;

}

bool Image::addPoint(QPointF mousePos, int polygonIndex, PolygonItem *parentShape)
{
    qreal x = mousePos.x();
    qreal y = mousePos.y();
    QGraphicsEllipseItem *shape;
    if (parentShape == nullptr)
    {
        shape =  new Point(-3,-3,6,6,this);
        points.push_back(shape);
    }
    else
    {
        shape =  new Point(-3,-3,6,6,polygonIndex,parentShape);
    }
    shape->setPos(x,y);
    shape->setPen(pens["pointPen"]);
    shape->setBrush(brushes["pointBrush"]);
    shape->setZValue(50);
    return true;
}

bool Image::addLine(QPointF point1, QPointF point2)
{
    QGraphicsLineItem *line = new QGraphicsLineItem(point1.x(), point1.y(),
                                                     point2.x(), point2.y(),
                                                  this);
    line->setPen(pens["linePen"]);
    lines.push_back(line);
    return true;
}

bool Image::addShape(QPolygonF shapePoints)
{

    PolygonItem *shape = new PolygonItem(shapePoints, this);
    shape->setFlag(PolygonItem::ItemIsMovable);
    shape->setFlag(PolygonItem::ItemIsSelectable);
    shape->setPen(pens["shapePen"]);
    shapes.push_back(shape);


    return true;
}


bool Image::deleteShape(PolygonItem *shapeToDelete)
{
    for(unsigned i=0; i < shapes.size(); i++)
    {
        if (shapes[i] == shapeToDelete)
        {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
            break;
        }

    }

    return true;
}


                                     //! If resize mode3 on 'shrink' or 'grow' resize function will execute.
void Image::growShape(PolygonItem *shapeToResize)
{
    QPolygonF shapePoints;
    QPolygon newShapePoints;
    shapePoints = shapeToResize->polygon();
    PolygonItem *shape = shapeToResize;
    shape->setTransformOriginPoint(shapePoints[0]);
    shape->setScale(1.2);
    for(int i = 0; i < shapePoints.size(); i++)
    {


    }
    shape->setSelected(false);

}

void Image::shrinkShape(PolygonItem *shapeToResize)
{
    QPolygonF shapePoints;
    shapePoints = shapeToResize->polygon();
    PolygonItem *shape = shapeToResize;
    shape->setTransformOriginPoint(shapePoints[0]);
    shape->setScale(0.8);

}

void Image::assignClassifierToSelectedShapes(QString c, int lineIndex)
{
    std::vector<PolygonItem * > shapesToAssign = findSelectedShapes();
    for(unsigned i=0; i < shapesToAssign.size(); i++)
    {
        shapesToAssign[i]->assignClassifier(c, lineIndex);

    }
}

void Image::loadImageData(QTextStream *read)
{
    QString line = read->readLine();
    int numberOfShapes = line.toInt();
    QStringList loadedShapePoints;

    for(int i=0; i!=numberOfShapes; i++)
    {
        line = read->readLine();
        int classifierIndex = line.toInt();
        QString classifierText = ""; //match the index too text
        std::pair<QString,int> classifier = {classifierText, classifierIndex};

        line = read->readLine();
        loadedShapePoints = line.split(";");
        QStringList loadedCoordinates;
        qreal x;
        qreal y;
        QPolygonF loadedPolygon = {};
        foreach(QString loadedPoint, loadedShapePoints)
        {
            loadedPoint.remove("(");
            loadedPoint.remove(")");
            loadedCoordinates = loadedPoint.split(",");
            x = loadedCoordinates[0].toDouble();
            y = loadedCoordinates[1].toDouble();
            QPointF loadedQPoint(x,y);
            loadedPolygon.push_back(loadedQPoint);
        }

        addShape(loadedPolygon);
        shapes.back()->assignClassifier(classifier.first,classifier.second);
    }
}

void Image::writeImageData(QTextStream *write, std::string name)
{
    QString qName = QString::fromStdString(name);
    *write << qName << "\n";
    unsigned length = shapes.size();
    *write << length << "\n";
    for(unsigned i=0; i < shapes.size(); i++)
    {
        shapes[i]->writeShapeData(write);
    }
}



bool Image::addDrawnShape()
{
    std::string mode2 = model->requestMode2();
    QPolygonF shapePoints = {};
    for(unsigned i=0; i < points.size(); i++) {
        QPointF nextPoint = points[i]->pos();
        shapePoints.append(nextPoint);
    }

    addShape(shapePoints);

    if (mode2=="copy"){                                    // duplicate of the drawn shape is created
        addShape(shapePoints);
    }

    for(unsigned i=0; i < points.size(); i++) {
        points[i]->setParentItem(NULL);
        delete points[i];
    }
    points = {};

    for(unsigned i=0; i < lines.size(); i++) {
        lines[i]->setParentItem(NULL);
        delete lines[i];
    }
    lines = {};

    return true;
}

void Image::copyPasteShapes(std::vector<PolygonItem *> shapesToCopyPaste)
{

    qreal pasteOffset = 50;
    QPointF pos;
    QPolygonF shapePoints;

    for(unsigned i=0; i < shapesToCopyPaste.size(); i++)
    {
        QString name = shapesToCopyPaste[i]->getClassifier();
        int lineIndex = shapesToCopyPaste[i]->getLineIndex();

        shapesToCopyPaste[i]->setSelected(false);
        shapePoints = shapesToCopyPaste[i]->polygon();
        pos = shapesToCopyPaste[i]->pos();
        pos.setX(pos.x() + pasteOffset);
        pos.setY(pos.y() + pasteOffset);
        addShape(shapePoints);
        shapes.back()->setPos(pos);
        shapes.back()->setSelected(true);      
        assignClassifierToSelectedShapes(name, lineIndex);
    }
}

void Image::copyPasteSelectedShapes()
{
    copyPasteShapes(findSelectedShapes());
}

void Image::growSelectedShapes()
{
    std::vector<PolygonItem * > shapesToResize = findSelectedShapes();
    for(unsigned i=0; i < shapesToResize.size(); i++)
    {
        growShape(shapesToResize[i]);
    }

}

void Image::shrinkSelectedShapes()
{
    std::vector<PolygonItem * > shapesToResize = findSelectedShapes();
    for(unsigned i=0; i < shapesToResize.size(); i++)
    {
        shrinkShape(shapesToResize[i]);
    }

}


void Image::deleteSelectedShapes()
{
    std::vector<PolygonItem * > shapesToDelete = findSelectedShapes();
    for(unsigned i=0; i < shapesToDelete.size(); i++)
    {
        deleteShape(shapesToDelete[i]);
    }
}

std::vector<PolygonItem * > Image::findSelectedShapes()
{

    std::vector<PolygonItem * > selectedShapes = {};
    for(unsigned i=0; i < shapes.size(); i++)
    {
        if (shapes[i]->isSelected())
        {
            selectedShapes.push_back(shapes[i]);
        }
    }
    return selectedShapes;
}

bool Image::connectLastDrawnPoints()
{
    QGraphicsEllipseItem * lastDrawnPoint = points[points.size() - 1];
    QGraphicsEllipseItem * secondToLastDrawnPoint = points[points.size() - 2];
    QPointF lastDrawnPosition = secondToLastDrawnPoint->pos();
    QPointF secondTolastDrawnPosition = lastDrawnPoint->pos();

    addLine(lastDrawnPosition, secondTolastDrawnPosition);
    return true;
}

void Image::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   mousePos = (event->scenePos());

    if (event->buttons() == Qt::LeftButton)
    {
        std::string mode = model->requestMode();
        if (mode == "draw")
        {
            if(addPoint(mousePos))
            {
                model->pointDrawn();
            }
        }
        update();
    }
    QGraphicsPixmapItem::mousePressEvent(event);
}

