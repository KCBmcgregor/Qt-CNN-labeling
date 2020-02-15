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

void View::on_shapeDrawButton_clicked()
{
    QString folderPathQString = QString::fromStdString(control->getFolderPath());
    ui->imageNameLabel->setText(folderPathQString);
}


View::~View()
{
    delete ui;
}

void View::on_imageNamesList_currentItemChanged(QListWidgetItem *current)
{
    ui->imageNameLabel->setText(current->text());
}
