#include "view.h"
#include "ui_view.h"
#include "linkedlist.h"
#include "image.h"
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QTextEdit>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include<QDataStream>


View::View(Control *cont, QWidget *parent): QMainWindow(parent), ui(new Ui::View)
{
    control = cont;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    image = new QGraphicsPixmapItem();
    ui->graphicsView->setScene(scene);

    ui->shapeDrawButton->setStyleSheet("background-color:white;\nborder:1px solid black;");

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

void View::renderList1()
{
    ui->imageNamesList->clear();

    QStringList imageNames = control->requestImageNames();
    foreach (QString name, imageNames) {
        ui->imageNamesList->addItem(name);
    }
}

void View::renderList2()
{
     ui->classifierList->clear();

    QStringList classifierNames = control->requestClassifierNames();
    foreach (QString name, classifierNames)
    {
        if ( name!= "***DELETED***")
        {
            ui->classifierList->addItem(name);
        }
    }
}

void View::on_selectFolderButton_clicked()
{
    QString path = control->requestFolderPath();
    ui->folderPathLabel->setText(path);
    ui->sortButton->setEnabled(true);
    ui->shapeDrawButton->setEnabled(true);

}

void View::on_selectFileButton_clicked()
{
    QString path = control->requestFilePath();
    ui->classiferPathLabel->setText(path);
    ui->sortButton2->setEnabled(true);
    ui->shapeAssignButton->setEnabled(true);
    ui->addClassButton->setEnabled(true);
    ui->removeClassButton->setEnabled(true);
}

void View::on_selectAnnotationFileButton_clicked()
{
    QString path = control->requestAnnotationPath();
    ui->selectFolderButton->setEnabled(true);
    ui->selectFileButton->setEnabled(true);
    ui->saveButton->setEnabled(true);
    //ui->annotationPathLabel->setText(path);
}

                                        //! When sortButton is clicked it retrieves imageComboBox current item..
void View::on_sortButton_clicked(){     //! ..and chooses the sorting algorithm based on that
    if(ui->imageNamesList->count() != 0) {
           ui->imageNamesList->clear();
           if(ui->ImageComboBox->currentText() =="Name (Asc)"){
               QStringList imageNames = control->retrieveListDataAscending(1);  //! 1 is passed as parameter meaning...
               foreach (QString name, imageNames) {     //! ..The data sorted using the ascending algorithm is image names
                   ui->imageNamesList->addItem(name);
               }
            }

            if(ui->ImageComboBox->currentText() =="Name (Des)"){
               QStringList imageNames = control->retrieveListDataDescending(1);
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
}
                                        //! When sortButton3 is clicked it retrieves classComboBox current item..
void View::on_sortButton2_clicked(){   //! ..and chooses the sorting algorithm based on that
    if(ui->classifierList->count() != 0) {
        ui->classifierList->clear();
        if(ui->classComboBox->currentText()=="Name (Asc)"){
            QStringList classifierNames = control->retrieveListDataAscending(2); //! 2 is passed as parameter meaning...
            foreach (QString name, classifierNames) {  //! ..the data sorted using the ascending algorithm is classifier names
                if ( name!= "***DELETED***")
                {
                    ui->classifierList->addItem(name);
                }

            }
        }
        if(ui->classComboBox->currentText()=="Name (Des)"){
            QStringList classifierNames = control->retrieveListDataDescending(2);
            foreach (QString name, classifierNames) {
                if ( name!= "***DELETED***")
                {
                    ui->classifierList->addItem(name);
                }
             }
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

void View::on_classifierList_currentItemChanged(QListWidgetItem *current)
{
    control->setSelectedClassifier(current->text());

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
   control->requestSave();
}



void View::on_addClassButton_clicked(){
    ui->classifierList->blockSignals(true);

    QString addClass = ui->addClassTextEdit->toPlainText();
    QString path = QString::fromStdString(control->getFilePath());

    if(addClass.isEmpty() || addClass.length() < 10){

        QFile outfile(path);
        outfile.open(QIODevice::Append);
        QTextStream out(&outfile);
        out <<"\n"<< addClass;

        ui->addClassTextEdit->clear();
        ui->classifierList->clear();
        ui->classifierList->blockSignals(false);

    }
}

void View::on_removeClassButton_clicked()
{
    QString classToRemove = control->getSelectedClassifier();
    QString path = QString::fromStdString(control->getFilePath());
    QFile outfile(path);

    outfile.open(QIODevice::Text | QIODevice::ReadWrite);
    QString dataText = outfile.readAll();

    QRegularExpression textToReplace(classToRemove);
    QString replacementText("***DELETED***");
    dataText.replace(textToReplace, replacementText);
    outfile.seek(0);

    QTextStream out(&outfile);
    out << dataText;
    ui->classifierList->blockSignals(true);
    ui->classifierList->clear();
    ui->classifierList->blockSignals(false);
}


void View::on_shapeAssignButton_clicked()
{
    control->requestAssignClassifierToSelectedShapes();
}




void View::on_createAnnotationFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Annotations"), "",
             tr("Annotation (*.annotations);;All Files (*)"));

     if (fileName.isEmpty())
           return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::WriteOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }
}
}
