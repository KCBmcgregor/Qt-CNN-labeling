#include "view.h"
#include "ui_view.h"
#include <QGraphicsPixmapItem>

View::View(Control *cont, QWidget *parent): QMainWindow(parent), ui(new Ui::View)
{
    control = cont;
    ui->setupUi(this);
    scene = new QGraphicsScene();
    sceneImage = new QGraphicsPixmapItem();;
}


void View::renderLists()
{
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
    QString selectedImageName = current->text();
    ui->imageNameLabel->setText(selectedImageName);
    QPixmap image = control->requestImage(selectedImageName);

    QGraphicsPixmapItem *oldSceneImage = sceneImage;
    scene->removeItem(sceneImage);

    sceneImage = scene->addPixmap(image);
    ui->graphicsView->setScene(scene);
    delete oldSceneImage;
}

View::~View()
{
    delete ui;
}
