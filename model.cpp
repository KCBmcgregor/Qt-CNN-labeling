#include "model.h"
#include "image.h"

#include <QFile>
#include <QString>
#include <QMainWindow>
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include<QDataStream>
Model::Model(Control *cont)
{
    control = cont;
    imageNames = {};
    imageNameDatesAsc = {};
    imageNameDatesDec = {};
    images = {};
    classifierNames = {};

}

QMap<std::string, QPen> Model::requestPens()
{
    return control->requestPens();
}

QGraphicsPixmapItem * Model::requestImageItem(std::string imageName)
{
    if (images.find(imageName) == images.end()) {
      return nullptr;
    }
    else
    {
      return (images[imageName]);
    }
}

int Model::requestNumberOfShapes(std::string imageName)
{
    return images[imageName]->getNumberOfShapes();
}

std::string Model::requestMode()
{
    std::string mode = control->getMode();
    return mode;
}
std::string Model::requestMode2()
{
    std::string mode2 = control->getMode2();
    return mode2;
}

std::string Model::requestMode3()
{
    std::string mode3 = control->getMode3();
    return mode3;
}

void Model::requestConnectLastDrawnPoints(std::string imageName)
{
    images[imageName]->connectLastDrawnPoints();
}

void Model::requestAddDrawnShape(std::string imageName)
{
    images[imageName]->addDrawnShape();

}
void Model::requestAssignClassifierToSelectedShapes(std::string imageName, QString c, int lineIndex)
{
    images[imageName]->assignClassifierToSelectedShapes(c, lineIndex);
}


std::string Model::loadDataset(std::string folderPath)
{
    const QStringList filter = {"*.jpg","*.JPG","*.png"};
    QString qFolderPath = QString::fromStdString(folderPath);
    QDir dir(qFolderPath);
    QStringList images = dir.entryList(filter);
    std::vector<std::string> newImageNames = control->qStringListToVector(images);
    imageNames = newImageNames;

    QStringList imagesAsc = dir.entryList(filter, QDir::Files, QDir::Time);                 //! Sorts image files by date ascending
    std::vector<std::string> newImageNamesAsc = control->qStringListToVector(imagesAsc);
    imageNameDatesAsc = newImageNamesAsc;

    QStringList imagesDec = dir.entryList(filter, QDir::Files, QDir::Time| QDir::Reversed); //! Sorts image file by date descending
    std::vector<std::string> newImageNamesDec = control->qStringListToVector(imagesDec);
    imageNameDatesDec = newImageNamesDec;
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
    Image *newImage;
    newImage = new Image(imagePath, this);
    std::string index = imageName.toStdString();
    images[index] = newImage;
}


Model::~Model()
{
    delete this;
}
