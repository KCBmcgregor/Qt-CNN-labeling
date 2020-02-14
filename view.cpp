#include "view.h"
#include "ui_view.h"
#include "control.h"

#include <QFileDialog>

View::View(Control *cont, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    control = cont;
    ui->setupUi(this);

}

View::~View()
{
    delete ui;
}

void View::on_selectFolderButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Select a dataset folder", "C://");
    std::string folderPathStr = folderPath.toStdString();
    control->setFolderPath(folderPathStr);
    ui->folderPathLabel->setText(folderPath);
}

void View::on_shapeDrawButton_clicked()
{
    QString folderPathQString = QString::fromStdString(control->folderPath);
    ui->imageNameLabel->setText(folderPathQString);
}
