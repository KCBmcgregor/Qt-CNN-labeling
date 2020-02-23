#include "model.h"
#include "imagedata.h"

#include <QFile>
#include <QString>
#include <QMainWindow>

Model::Model(Control *cont)
{
    control = cont;
    imageNames = {};
    imageData = {};
    classifierNames = {};

}

QMap<std::string, QPen> Model::requestPens()
{
    return control->requestPens();
}

QGraphicsPixmapItem * Model::requestImageItem(std::string imageName)
{
    if (imageData.find(imageName) == imageData.end()) {
      return nullptr;
    }
    else
    {
      return (imageData[imageName]->getImagePt());
    }
}

std::string Model::requestMode()
{
    std::string mode = control->getMode();
    return mode;
}

std::string Model::loadDataset(std::string folderPath)
{
    const QStringList filter = {"*.jpg","*.JPG","*.png"};
    QString qFolderPath = QString::fromStdString(folderPath);
    QDir dir(qFolderPath);
    QStringList images = dir.entryList(filter);
    std::vector<std::string> newImageNames = control->qStringListToVector(images);
    imageNames = newImageNames;
    return folderPath;
}

std::string Model::loadClassifers(std::string filePath)
{
    QString qFilePath = QString::fromStdString(filePath);
    QFile file(qFilePath);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {

    }
    else
    {
        classifierNames = {};
        QTextStream in(&file);
        QString line;
        std::string stringLine;
        while (!(in.atEnd())) {
            line = in.readLine();
            stringLine = line.toStdString();
            classifierNames.push_back(stringLine);
        }
    }
    return filePath;
}

void Model::loadImage(QString imagePath, const QString imageName)
{
    ImageData *newImageData;
    newImageData = new ImageData(imagePath, this);
    std::string index = imageName.toStdString();
    imageData[index] = newImageData;
}


Model::~Model()
{
    delete this;
}
