#ifndef MODEL_H
#define MODEL_H

#include "control.h"
#include "imagedata.h"

#include <QStringListModel>

#include <map>

class Model
{
    Control *control;
    std::vector<std::string> imageNames;
    std::map<std::string, ImageData * > imageData;
    std::vector<std::string> classifierNames;
    std::vector<QDateTime>dates;
public:
    Model(Control *cont = nullptr);

    std::vector<std::string> getImageNames() {return imageNames;}
    std::vector<std::string> getClassifierNames() {return classifierNames;}

    QMap<std::string,QPen> requestPens();
    QGraphicsPixmapItem * requestImageItem(std::string imageName);
    std::string requestMode();
    void requestConnectLastDrawnPoints(std::string imageName);
    void requestAddDrawnShape(std::string imageName);

    std::string loadDataset(std::string folderPath);
    std::string loadClassifers(std::string filePath);
    void loadImage(QString imagePath, const QString imageName);

    void pointDrawn() {control->pointDrawn();}

    std::vector<QDateTime> getDates() {return dates;}
    std::string loadDataset(std::string folderPath);
    std::string loadClassifers(std::string filePath);
    std::vector<QDateTime>loadDates(std::vector<std::string> imageNames);
    QPixmap loadImage(const QString imagePath);

    ~Model();
};

#endif // MODEL_H
