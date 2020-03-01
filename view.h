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

//! A public class.
/*!
The view holds all of the button slots, user interface, 5
*/

//! Uses a pointer to allow access into other classes methods.
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

    //!A list of all pens
    /*!
    The QMap is an access method used to retrieve data it stores a list of all pen objects; line, shape, .appoint to be used when drawing shapes
    */

    QMap<std::string,QPen> getPens() {return pens;}

    //!A public method used to update the lists
    /*!
    When run the two list widgets, holding image and classifier names are updated to the latest values in the model.
    */
    void renderLists();

    void renderList1();
    void renderList2();

    ~View();

private slots:
    //! A private method for select folder button
    /*!
    selectFolderButton is a public library function slot which is activated when clicked by the user.
    */
    void on_selectFolderButton_clicked();
    //! A private method for select file button
    /*!
    selectFileButton is a public library function slot which is activated when clicked by the user.
    */
    void on_selectFileButton_clicked();
    //! A private method for sort button
    /*!
    sortButton is a public library function slot which is activated when clicked by the user.
    */
    void on_sortButton_clicked();
    void on_sortButton2_clicked();

    void on_imageNamesList_currentItemChanged(QListWidgetItem *current);
    //! A private method for shape draw button
    /*!
    shapeDrawButton is a public library function slot which is activated when clicked by the user.
    */
    void on_shapeDrawButton_clicked();

    void on_shapesList_currentItemChanged(QListWidgetItem *current);
    //! A private method for zoom in button
    /*!
    zoomInButton is a public library function slot which is activated when clicked by the user.
    */
    void on_zoomInButton_clicked();
    //! A private method for zoom out button
    /*!
    selectFolderButton is a public library function slot which is activated when clicked by the user.
    */
    void on_zoomOutButton_clicked();
    //! A private method for copy/paste button
    /*!
    copyPasteButton is a public library function slot which is activated when clicked by the user.
    */
    void on_copyPasteButton_clicked();
    //! A private method for resize  button
    /*!
    resizeButton is a public library function slot which is activated when clicked by the user.
    */
    void on_resizeButton_clicked();
    //! A private method for save button
    /*!
    saveButton is a public library function slot which is activated when clicked by the user.
    */
    void on_saveButton_clicked();

};

#endif // VIEW_H
