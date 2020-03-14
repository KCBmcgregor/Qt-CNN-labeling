#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <string>
#include <map>
#include <vector>
#include <QGraphicsItem>
#include <QMenu>
#include <view.h>
#include <polygonitem.h>

#include <QStringListModel>

#include <map>

class Image;

class Model
{
    Control *control;
    std::vector<std::string> imageNames;
    std::map<std::string, Image * > images;
    std::vector<std::string> classifierNames;
    std::vector<std::string> imageNameDatesAsc;
    std::vector<std::string> imageNameDatesDec;
public:
    Model(Control *cont = nullptr);

    std::vector<std::string> getImageNames() {return imageNames;}
    std::vector<std::string> getClassifierNames() {return classifierNames;}
    std::vector<std::string> getImageNameDatesAsc() {return imageNameDatesAsc;}
    std::vector<std::string> getImageNameDatesDec() {return imageNameDatesDec;}

    QMap<std::string,QPen> requestPens();
    QGraphicsPixmapItem * requestImageItem(std::string imageName);
    int requestNumberOfShapes(std::string imageName);
    std::string requestMode();
    std::string requestMode2();
    std::string requestMode3();
    void requestConnectLastDrawnPoints(std::string imageName);
    void requestAddDrawnShape(std::string imageName);
    void requestAssignClassifierToSelectedShapes(std::string imageName, QString c, int lineIndex);

    std::string loadDataset(std::string folderPath);
    std::string loadClassifers(std::string filePath);
    void loadImage(QString imagePath, const QString imageName);
    QPixmap loadImage(const QString imagePath);

    void pointDrawn() {control->pointDrawn();}






    ~Model();
};

#endif // MODEL_H
