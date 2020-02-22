#include "model.h"
#include "view.h"
#include "control.h"
#include <string>

#include <QtCore>
#include <QApplication>
#include <QFileDialog>


//Control constructor
Control::Control() {
    folderPath = "Please Select Your Dataset Folder >>";
    classifierFilePath = "Please Select Your Class File >>";
    mode = "none";
    sidesToDraw = 0;
}
void Control::setSidesToDraw(QString shape) {
    sidesToDraw = shape.mid(0).toInt();
}

QStringList Control::requestImageNames()
{
    std::vector<std::string> namesVector = model->getImageNames();
    QStringList names = vectorToQStringList(namesVector);
    return names;
}

QStringList Control::requestClassifierNames()
{
    std::vector<std::string> namesVector = model->getClassifierNames();
    QStringList names = vectorToQStringList(namesVector);
    return names;
}

QString Control::requestFolderPath()
{
    QString QStringFolderPath = QFileDialog::getExistingDirectory(view, "Select a dataset folder", "C://");
    folderPath = QStringFolderPath.toStdString();
    model->loadDataset(folderPath);
    view->renderLists();
    return QStringFolderPath;
}

QString Control::requestFilePath()
{
    QString filter = "Class Files (*.names)";
    QString QStringFilePath = QFileDialog::getOpenFileName(view, "Select your class file", "C://",filter);
    classifierFilePath = QStringFilePath.toStdString();
    model->loadClassifers(classifierFilePath);
    view->renderLists();
    return QStringFilePath;
}

QGraphicsPixmapItem * Control::requestImage(const QString imageName)
{
    QGraphicsPixmapItem *image = model->requestImageItem(imageName.toStdString());
    if (image == nullptr)
    {
        QString qFolderPath = QString::fromStdString(folderPath);
        QString imagePath = qFolderPath + "/" + imageName;
        model->loadImage(imagePath, imageName);
        image = model->requestImageItem(imageName.toStdString());
    }
    return image;
}

QStringList Control::vectorToQStringList(std::vector<std::string> v)
{
    QStringList returnList;
    for(unsigned i=0; i < v.size(); i++) {
        QString item = QString::fromStdString(v[i]);
        returnList.append(item);
    }
    return returnList;
}

std::vector<std::string> Control::qStringListToVector(QStringList list)
{
    std::vector<std::string> returnVector;
    foreach(QString QStringItem, list) {
        std::string item = QStringItem.toStdString();
        returnVector.push_back(item);
    }
    return returnVector;
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Control control;
    Model model(&control);
    control.model = &model;
    View view(&control);
    control.view = &view;

    view.setWindowTitle("CNN Image Labeling");
    view.show();

    return app.exec();
}
