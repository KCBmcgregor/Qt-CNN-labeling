#ifndef VIEW_H
#define VIEW_H
#include "control.h"
//#include "imagedata.h"
#include <QListWidgetItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsItem>
class ImageData;

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

/*!
 \brief

*/
class View : public QMainWindow
{
    Q_OBJECT

private:
    Ui::View *ui; /*!< TODO: describe */
    Control *control; /*!< TODO: describe */
    QGraphicsScene *scene; /*!< TODO: describe */
    QGraphicsPixmapItem *image; /*!< TODO: describe */
    QMap<std::string,QPen> pens; /*!< TODO: describe */


public:
    /*!
     \brief

     \param cont
     \param parent
    */
    View(Control *cont = nullptr,QWidget *parent = nullptr);


    /*!
     \brief

     \return QMap<std::string, QPen>
    */
    QMap<std::string,QPen> getPens() {return pens;}

    /*!
     \brief

    */
    void renderLists();

    /*!
     \brief

    */
    void renderList1();
    /*!
     \brief

    */
    void renderList2();

    /*!
     \brief

    */
    ~View();

private slots:
    /*!
     \brief

    */
    void on_selectFolderButton_clicked();
    /*!
     \brief

    */
    void on_selectFileButton_clicked();
    /*!
     \brief

    */
    void on_sortButton_clicked();
    /*!
     \brief

    */
    void on_sortButton2_clicked();

    /*!
     \brief

     \param current
    */
    void on_imageNamesList_currentItemChanged(QListWidgetItem *current);
    /*!
     \brief

    */
    void on_shapeDrawButton_clicked();
    /*!
     \brief

     \param current
    */
    void on_shapesList_currentItemChanged(QListWidgetItem *current);
    /*!
     \brief

    */
    void on_zoomInButton_clicked();
    /*!
     \brief

    */
    void on_zoomOutButton_clicked();
    /*!
     \brief

    */
    void on_copyPasteButton_clicked();
    /*!
     \brief

    */
    void on_resizeButton_clicked();
    /*!
     \brief

    */
    void on_saveButton_clicked();

};

#endif // VIEW_H
