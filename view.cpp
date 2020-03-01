#include "view.h"
#include "ui_view.h"
#include <QGraphicsPixmapItem>
#include <QFileDialog>

View::View(Control *cont, QWidget *parent): QMainWindow(parent), ui(new Ui::View)
{
    control = cont;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    image = new QGraphicsPixmapItem();
    ui->graphicsView->setScene(scene);

    ui->copyPasteButton->setStyleSheet("background-color:white;\nborder:1px solid black;");

    ui->shapeDrawButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
    ui->saveButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
    ui->shapeUnassignButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
    //ui->shapeSelectButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
    ui->toggleClassifierButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
    ui->resizeButton->setStyleSheet("background-color:white;\nborder:1px solid black;");

    QPen pointPen(Qt::red);
    pointPen.setWidth(1);
    pens["pointPen"] = pointPen;

    QPen linePen(Qt::black);
    linePen.setWidth(6);
    pens["linePen"] = linePen;

    QPen shapePen(Qt::green);
    shapePen.setWidth(6);
    pens["shapePen"] = shapePen;


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
                                        //! When sortButton is clicked it retrieves imageComboBox current item..
void View::on_sortButton_clicked(){     //! ..and chooses the sorting algorithm based on that
    ui->imageNamesList->clear();
    if(ui->ImageComboBox->currentText() =="Name (Asc)"){
        QStringList imageNames = control->requestSortedNameAscending(1);  //! 1 is passed as parameter meaning...
        foreach (QString name, imageNames) {     //! ..The data sorted using the ascending algorithm is image names
            ui->imageNamesList->addItem(name);
        }
     }

     if(ui->ImageComboBox->currentText() =="Name (Des)"){
        QStringList imageNames = control->requestSortedNameDescending(1);
        foreach (QString name, imageNames) {
            ui->imageNamesList->addItem(name);
        }
    }
     if(ui->ImageComboBox->currentText() =="Date (Asc)"){              //! Sorting images by their dates
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
                                        //! When sortButton3 is clicked it retrieves classComboBox current item..
void View::on_sortButton2_clicked(){   //! ..and chooses the sorting algorithm based on that
    ui->classifierList->clear();
    if(ui->classComboBox->currentText()=="Name (Asc)"){
        QStringList classifierNames = control->requestSortedNameAscending(2); //! 2 is passed as parameter meaning...
        foreach (QString name, classifierNames) {  //! ..the data sorted using the ascending algorithm is classifier names
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
               //! The copypaste function is only valid when the user preselects the draw function..
void View::on_shapeDrawButton_clicked()   //! ..so this function validates this and sets the modes/button styles
{

    if (control->getMode()=="draw")
    {
        if(control->getMode2()=="copy")
        {                               //! When draw mode is deselected, if mode2 (copyPaste) is active it's also deselected
            control->setMode2("");
            ui->copyPasteButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
        }
        control->setMode("");
        ui->shapeDrawButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
    }
    else
    {
        control->setMode("draw");
        ui->shapeDrawButton->setStyleSheet("background-color:#A3C1DA;\nborder:1px solid black;");

    }

}
                              //! Copypaste function sets mode2 to copy so the current shape being drawn is copied
void View::on_copyPasteButton_clicked()
{
    if (control->getMode2()=="copy"){
        control->setMode2("");
        ui->copyPasteButton->setStyleSheet("background-color:white;\nborder:1px solid black;");
    }
    else
    {
        if(control->getMode()=="draw")
        {
            control->setMode2("copy");
            ui->copyPasteButton->setStyleSheet("background-color:#A3C1DA;\nborder:1px solid black;");
        }


    }

}
//! Resize sets mode3 to either grow or shrink, so the shape selected is resized accordingly.
void View::on_resizeButton_clicked()
{
    if(control->getMode3()=="shrink"){

        control->setMode3("grow");
        ui->resizeButton->setStyleSheet("background-color:red;\nborder:1px solid black;");
        ui->resizeButton->setText("Grow Shape");
    }
    else{
        control->setMode3("shrink");
        ui->resizeButton->setStyleSheet("background-color:green;\nborder:1px solid black;");
        ui->resizeButton->setText("Shrink Shape");
    }
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

void View::on_saveButton_clicked()
{
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
        if (!fileName.isNull())
        {
            QPixmap pixMap = this->ui->graphicsView->grab();
            pixMap.save(fileName);
        }
}
