#include "model.h"
#include "view.h"
#include "control.h"
#include <string>

#include <QApplication>
#include <QFileDialog>


//Control constructor
Control::Control() {
    folderPath = "C//:";

}
std::string Control::getFolderPath() {return folderPath;}

void Control::setFolderPath(std::string path) {
    folderPath = path;
}




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Control control;
    Model model(&control);
    View view(&control);


    view.setWindowTitle("CNN Image Labeling");
    view.show();

    return app.exec();

}
