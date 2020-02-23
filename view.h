#ifndef VIEW_H
#define VIEW_H
#include "control.h"

#include <QListWidgetItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>

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

    QMap<std::string,QPen> getPens() {return pens;}

    void renderLists();

    ~View();

private slots:
    void on_selectFolderButton_clicked();
    void on_selectFileButton_clicked();

    void on_imageNamesList_currentItemChanged(QListWidgetItem *current);
    void on_shapeDrawButton_clicked();
    void on_shapesList_currentItemChanged(QListWidgetItem *current);
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
};

#endif // VIEW_H
