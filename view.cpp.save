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

    QPen linePen(Qt::black);
    linePen.setWidth(5);


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
        QPixmap image = control->requestImage(selectedImageName);

        QGraphicsPixmapItem *oldSceneImage = sceneImage;
        scene->removeItem(sceneImage);

        sceneImage = scene->addPixmap(image);
        ui->graphicsView->centerOn(sceneImage);
        delete oldSceneImage;
    }
    else
    {
        QGraphicsPixmapItem *oldSceneImage = sceneImage;
        scene->removeItem(sceneImage);
        delete oldSceneImage;
        sceneImage = new QGraphicsPixmapItem();
    }
}

View::~View()
{
    delete ui;
}

void View::on_shapeDrawButton_clicked()
{
    QPen linePen(Qt::black);
    linePen.setWidth(5);

    rectangle = scene->addRect(10,10,100,100,linePen);
    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
    rectangle->setFlag(QGraphicsItem::ItemIsSelectable);

    rectangle = scene->addRect(-10,-10,100,100,linePen);
    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
    rectangle->setFlag(QGraphicsItem::ItemIsSelectable);
}
