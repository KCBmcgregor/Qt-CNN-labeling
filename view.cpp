#include "view.h"
#include "ui_view.h"

View::View(Control *cont, QWidget *parent): QMainWindow(parent), ui(new Ui::View)
{
    control = cont;
    ui->setupUi(this);
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
    int w = (ui->imageDiplayLabel->width());
    int h = (ui->imageDiplayLabel->height());
    image.scaled(w,h,Qt::KeepAspectRatio);
    ui->imageDiplayLabel->setPixmap(image);
}


View::~View()
{
    delete ui;
}
