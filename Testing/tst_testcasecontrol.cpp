#include <QtTest>
#include<QtTest/QTest>
#include<QtWidgets/QGraphicsWidget>
#include<QtCore>
#include <QtWidgets/QGraphicsPixmapItem>

#include <QtWidgets/QFileDialog>

#include <QtWidgets/QListWidgetItem>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QPen>
#include <QtWidgets/QGraphicsItem>
#include<QtTestGui>




//class Image;

class Model
{
   // Control *control;
    std::vector<std::string> imageNames;
    //std::map<std::string, Image * > images;
    std::vector<std::string> classifierNames;
    std::vector<std::string> imageNameDatesAsc;
    std::vector<std::string> imageNameDatesDec;
public:
   // Model(Control *cont = nullptr);

    std::vector<std::string> getImageNames() {return imageNames;}
    std::vector<std::string> getClassifierNames() {return classifierNames;}
    std::vector<std::string> getImageNameDatesAsc() {return imageNameDatesAsc;}
    std::vector<std::string> getImageNameDatesDec() {return imageNameDatesDec;}


    std::string loadClassifers(std::string filePath);


  //  void pointDrawn() {control->pointDrawn();}






    ~Model();
};

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



QTEST_APPLESS_MAIN (Model)

#include "tst_testcasecontrol.moc"
