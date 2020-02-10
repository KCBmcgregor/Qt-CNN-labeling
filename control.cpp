#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    View view;
    view.setWindowTitle("CNN Image Labeling");
    view.show();
    return app.exec();
}
