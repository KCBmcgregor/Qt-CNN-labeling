#include "model.h"

#include <QFile>
#include <QString>
#include <QFileDialog>

Model::Model(Control *cont)
{
    control = cont;

    imageNames = {};

    imageData = {};

    classifierNames = {};

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

QPixmap Model::loadImage(const QString imagePath)
{
    QPixmap image(imagePath);
    return image;
}


Model::~Model()
{
    delete this;
}
