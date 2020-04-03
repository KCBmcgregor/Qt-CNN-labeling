#ifndef VIEW_H
#define VIEW_H
#include "control.h"
//#include "imagedata.h"
#include <QListWidgetItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsItem>
//#include<QtTest/QTest>


class ImageData;

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

private:
    Ui::View *ui;
    Control *control;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *image;
    QMap<std::string,QPen> pens;


public:
    View(Control *cont = nullptr,QWidget *parent = nullptr);
    //void setSelectionModel(QItemSelectionModel*  selectionModel);


    QMap<std::string,QPen> getPens() {return pens;}


    void renderList1();
    void renderList2();

    ~View();

private slots:
    void on_selectFolderButton_clicked();
    void on_selectFileButton_clicked();
    void on_sortButton_clicked();
    void on_sortButton2_clicked();
    void on_shapeDrawButton_clicked();

    void on_imageNamesList_currentItemChanged(QListWidgetItem *current);
    void on_classifierList_currentItemChanged(QListWidgetItem *current);
    void on_shapesList_currentItemChanged(QListWidgetItem *current);
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
    void on_saveButton_clicked();
    void on_addClassButton_clicked();
    void on_shapeAssignButton_clicked();
    void on_removeClassButton_clicked();
    void on_selectAnnotationFileButton_clicked();
};

#endif // VIEW_H
