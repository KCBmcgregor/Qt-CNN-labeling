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


void View::renderList1()
{
    ui->imageNamesList->clear();
    ui->classifierList->clear();

    QStringList imageNames = control->requestImageNames();
    foreach (QString name, imageNames) {
        ui->imageNamesList->addItem(name);
    }
}

void View::renderList2()
{
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

void View::on_sortButton_clicked(){
    ui->imageNamesList->clear();
    if(ui->ImageComboBox->currentText() =="Name (Asc)"){
        QStringList imageNames = control->requestSortedNameAscending(1);
        foreach (QString name, imageNames) {
            ui->imageNamesList->addItem(name);
        }
     }

     if(ui->ImageComboBox->currentText() =="Name (Des)"){
        QStringList imageNames = control->requestSortedNameDescending(1);
        foreach (QString name, imageNames) {
            ui->imageNamesList->addItem(name);
        }
    }
     if(ui->ImageComboBox->currentText() =="Name (Asc)"){
        QStringList imageNames = control->requestSortedDateAscending();
        foreach (QString name, imageNames) {
            ui->imageNamesList->addItem(name);
        }
    }
     if(ui->ImageComboBox->currentText() =="Date (Des)"){
        QStringList imageNames = control->requestSortedDateDescending();
        foreach (QString name, imageNames) {
            ui->imageNamesList->addItem(name);
        }
    }
}

void View::on_sortButton2_clicked(){
    ui->classifierList->clear();
    if(ui->classComboBox->currentText()=="Name (Asc)"){
        QStringList classifierNames = control->requestSortedNameAscending(2);
        foreach (QString name, classifierNames) {
            ui->classifierList->addItem(name);
        }
    }

    if(ui->classComboBox->currentText()=="Name (Des)"){
        QStringList classifierNames = control->requestSortedNameDescending(2);
        foreach (QString name, classifierNames) {
            ui->classifierList->addItem(name);
        }
    }
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
