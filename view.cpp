#include "view.h"
#include "ui_view.h"
#include <QGraphicsPixmapItem>

View::View(Control *cont, QWidget *parent): QMainWindow(parent), ui(new Ui::View)
{
    control = cont;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    sceneImage = new QGraphicsPixmapItem();
    ui->graphicsView->setScene(scene);



}


void View::renderLists()
{
    ui->imageNamesList->clear();
    ui->classifierList->clear();

    QStringList imageNames = control->requestImageNames();
    foreach (QString name, imageNames) {
        ui->imageNamesList->addItem(name);
    }
    QStringList classifierNames = control->requestClassifierNames();
    foreach (QString name, classifierNames) {
        ui->classifierList->addItem(name);
    }
}

void View::on_selectFolderButton_clicked()
{
    QString path = control->requestFolderPath();
    ui->folderPathLabel->setText(path);
}
void View::on_selectFileButton_clicked()
{
    QString path = control->requestFilePath();
    ui->classiferPathLabel->setText(path);
}

void View::on_imageNamesList_currentItemChanged(QListWidgetItem *current)
{
    if (current != nullptr)
    {
        QString selectedImageName = current->text();
        ui->imageNameLabel->setText(selectedImageName);
        scene->clear(); //this delets the items need a work around
        QGraphicsPixmapItem *image = control->requestImage(selectedImageName);
        scene->addItem(image);
        ui->graphicsView->centerOn(sceneImage);
    }
    else
    {
        scene->clear();
    }
}

View::~View()
{
    delete ui;
}

void View::on_shapeDrawButton_clicked()
{
    control->setMode("draw");
}

void View::on_shapesList_currentItemChanged(QListWidgetItem *current)
{
    control->setSidesToDraw(current->text());
}
