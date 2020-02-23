#include "view.h"
#include "ui_view.h"
#include <QGraphicsPixmapItem>

View::View(Control *cont, QWidget *parent): QMainWindow(parent), ui(new Ui::View)
{
    control = cont;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    image = new QGraphicsPixmapItem();
    ui->graphicsView->setScene(scene);


    QPen pointPen(Qt::red);
    pointPen.setWidth(10);
    pens["pointPen"] = pointPen;

    QPen linePen(Qt::black);
    linePen.setWidth(5);
    pens["linePen"] = linePen;

    QPen shapePen(Qt::green);
    shapePen.setWidth(10);
    pens["shapePen"] = shapePen;


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
        scene->removeItem(image);
        control->setSelectedImageName(selectedImageName.toStdString());
        image = control->requestImage(selectedImageName);
        scene->addItem(image);
        ui->graphicsView->centerOn(image);
    }
    else
    {
        scene->removeItem(image);
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

void View::on_zoomInButton_clicked()
{
    ui->graphicsView->scale(1.2,1.2);
}

void View::on_zoomOutButton_clicked()
{
    ui->graphicsView->scale(0.8,0.8);
}
