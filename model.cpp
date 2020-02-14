#include "model.h"

#include <QFile>
#include <QString>
#include <QFileDialog>

Model::Model(Control *cont)
{
    control = cont;

    imageNames = {"TestImage_name","TestImage_name_2"};

    imageData = {};

    classifierNames = {"testclass","testclass_2"};

}

std::string Model::loadDataset(std::string folderPath)
{
    const QStringList filter = {"*.jpg","*JPG"};
    QString qFolderPath = QString::fromStdString(folderPath);
    QDir dir(qFolderPath);
    QStringList images = dir.entryList(filter);
    std::vector<std::string> newImageNames = control->qStringListToVector(images);
    imageNames = newImageNames;


    return folderPath;
}

Model::~Model()
{
    delete this;
}
