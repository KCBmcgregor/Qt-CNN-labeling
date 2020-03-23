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
    sidesToDraw = 3;
    drawPointsDrawn = 0;
    drawSidesDrawn = 0;
    selectedClassifier.second = -1;
}
void Control::setSidesToDraw(QString shape) {
    sidesToDraw = shape.at(0).digitValue();
}

void Control::savingToFile()
{

}

int Control::requestNumberOfShapes()
{
     return model->requestNumberOfShapes(selectedImageName);
}

QMap<std::string, QPen> Control::requestPens()
{
    return view->getPens();
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
    view->renderList1();
    return QStringFolderPath;
}

QString Control::requestFilePath()
{
    QString filter = "Class Files (*.names)";
    QString QStringFilePath = QFileDialog::getOpenFileName(view, "Select your class file", "C://",filter);
    classifierFilePath = QStringFilePath.toStdString();
    model->loadClassifers(classifierFilePath);
    view->renderList2();
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

void Control::requestAssignClassifierToSelectedShapes()
{
    model->requestAssignClassifierToSelectedShapes
            (selectedImageName,selectedClassifier.first,selectedClassifier.second);
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


void Control::pointDrawn()
{
    drawPointsDrawn++;
    if (drawPointsDrawn == sidesToDraw)
    {
       model->requestAddDrawnShape(selectedImageName);
       drawPointsDrawn = 0;
    }
    else if (drawPointsDrawn != 1)
    {
        model->requestConnectLastDrawnPoints(selectedImageName);

    }
}

                // Takes parameter i, which determines the data being sorted(either image/classifier names) and sorts ascending

QStringList Control::requestSortedNameAscending(std::vector<std::string>namesVector){

    bool swapped = false;

    for (unsigned int i = 0; i < namesVector.size() - 1; ++i) {
        for (unsigned int j = 0; j < namesVector.size() - 1 - i; ++j) {

            if (namesVector[j] > namesVector[j + 1]) {
                std::string temp = namesVector[j];
                namesVector[j] = namesVector[j + 1];
                namesVector[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
    }
    QStringList sortedNames = vectorToQStringList(namesVector);
    return sortedNames;
}

QStringList Control::requestSortedNameDescending(std::vector<std::string>namesVector){

    bool swapped = false;

    for (unsigned int i = 0; i < namesVector.size() - 1; ++i) {
        for (unsigned int j = 0; j < namesVector.size() - 1 - i; ++j) {

            if (namesVector[j] < namesVector[j + 1]) {
                std::string temp = namesVector[j];
                namesVector[j] = namesVector[j + 1];
                namesVector[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
    }
    QStringList sortedNames = vectorToQStringList(namesVector);
    return sortedNames;
}


QStringList Control::retrieveListDataAscending(int i)
{
    std::vector<std::string>namesVector;
    if(i == 1){
        namesVector = model->getImageNames();
    }
    if(i == 2){
        namesVector = model->getClassifierNames();
    }
    QStringList sortedNames = requestSortedNameAscending(namesVector);
    return sortedNames;
}

QStringList Control::retrieveListDataDescending(int i)
{
    std::vector<std::string>namesVector;
    if(i == 1){
        namesVector = model->getImageNames();

    }
    if(i == 2){
        namesVector = model->getClassifierNames();
    }
    QStringList sortedNames = requestSortedNameDescending(namesVector);
    return sortedNames;
}

                // Takes parameter i, which determines the data being sorted(either image/classifier names) and sorts descending

                                                        // Sorts images by date in ascending order
QStringList Control::requestSortedDateAscending()
{
    std::vector<std::string>namesVector = model->getImageNameDatesAsc();
    QStringList sortedNames = vectorToQStringList(namesVector);
    return sortedNames;
}

QStringList Control::requestSortedDateDescending()
{
    std::vector<std::string>namesVector = model->getImageNameDatesDec();
    QStringList sortedNames = vectorToQStringList(namesVector);
    return sortedNames;
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
