#include "model.h"
#include "view.h"
#include "control.h"
#include <string>

#include <QtCore>
#include <QApplication>
#include <QFileDialog>


//Control constructor
Control::Control() {
    folderPath = "C//:";

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

QStringList Control::vectorToQStringList(std::vector<std::string> v)
{
    QStringList returnList;
    for(unsigned i=0; i < v.size(); i++) {
        QString item = QString::fromStdString(v[i]);
        returnList.append(item);
    }
    return returnList;
}

QString Control::requestFolderPath()
{
    QString QStringFolderPath = QFileDialog::getExistingDirectory(view, "Select a dataset folder", "C://");
    folderPath = QStringFolderPath.toStdString();
    view->renderLists();
    return QStringFolderPath;
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
