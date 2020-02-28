#ifndef MODEL_H
#define MODEL_H

#include "control.h"


#include <QStringListModel>

#include <map>

class Image;

class Model
{
    Control *control;
    std::vector<std::string> imageNames;
    std::map<std::string, Image * > images;
    std::vector<std::string> classifierNames;
    std::vector<QDateTime>dates;
public:
    Model(Control *cont = nullptr);

    std::vector<std::string> getImageNames() {return imageNames;}
    std::vector<std::string> getClassifierNames() {return classifierNames;}
    std::vector<QDateTime> getDates() {return dates;}

    QMap<std::string,QPen> requestPens();
    QGraphicsPixmapItem * requestImageItem(std::string imageName);
    std::string requestMode();
    std::string requestMode2();
    std::string requestMode3();
    void requestConnectLastDrawnPoints(std::string imageName);
    void requestAddDrawnShape(std::string imageName);

    std::string loadDataset(std::string folderPath);
    std::string loadClassifers(std::string filePath);
    void loadImage(QString imagePath, const QString imageName);
    std::vector<QDateTime>loadDates(std::vector<std::string> imageNames);
    QPixmap loadImage(const QString imagePath);

    void pointDrawn() {control->pointDrawn();}






    ~Model();
};

#endif // MODEL_H
