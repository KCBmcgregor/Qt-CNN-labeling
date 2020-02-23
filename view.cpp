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
    pointPen.setWidth(6);
    pens["pointPen"] = pointPen;



    QPen highlightPen(Qt::yellow);
    highlightPen.setWidth(10);



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
