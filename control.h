#ifndef CONTROL_H
#define CONTROL_H

#include <QtCore>
#include <QGraphicsPixmapItem>
#include <string>

class Model;
class View;


//! The Control class to control the program logic.
/*!
 The Control class will control the the program logic and manage the
 communication between the model and view objects it will also contain
 some variable about the current state of the program like the curently
 selected folder path.
*/

class Control
{
private:

    //! State variables for file paths.
    std::string folderPath; /**< string to hold the currently selected dataset folder path */
    std::string classifierFilePath; /**< string to hold the currently selected class file path */
    std::string selectedImageName;
    std::string mode;
    std::string mode2;
    std::string mode3; /*!< TODO: describe */
    int sidesToDraw; /*!< TODO: describe */

    int drawPointsDrawn; /*!< TODO: describe */
    int drawSidesDrawn; /*!< TODO: describe */


public:
    //! The Contol constructor.
    /*!
     \brief

    */
    Control();

    //! Public pointers to the Model & View objects.
    /*!
     the 3 main objects need to be able to call methods on each other
     therfore they need to hold pointers to eachother so they can do this.
     the pointers are used whenever an object need to call the other
     objects methods.
    */
    Model *model; /**< pointer to the Model object */
    View *view; /**< pointer to the View object */

    //! Access methods to the private variables.
    /**
     @return std::string
     */
    std::string getFolderPath() {return folderPath;}
    std::string getMode() {return mode;}
    std::string getMode2() {return mode2;}
    /*!
     \brief

     \return std::string
    */
    std::string getMode3() {return mode3;}
    /*!
     \brief

     \return int
    */
    int getSidesToDraw() {return sidesToDraw;}

    /*!
     \brief

     \param iN
    */
    void setSelectedImageName(std::string iN) {selectedImageName = iN;}
    /*!
     \brief

     \param m
    */
    void setMode(std::string m) {mode = m;}
    /*!
     \brief

     \param m
    */
    void setMode2(std::string m) {mode2 = m;}
    /*!
     \brief

     \param m
    */
    void setMode3(std::string m) {mode3 = m;}
    /*!
     \brief

     \param shape
    */
    void setSidesToDraw(QString shape);

    /*!
     \brief

     \return QMap<std::string, QPen>
    */
    QMap<std::string,QPen> requestPens();

    //! A method taking no arguments and returning a QStringList.
    /*!
     requests a list of the current image names stored in the model
      @return list of the current image names  
    */

    std::vector<QDateTime> requestDates();
    //!takes no arguments and returns a vector of type QDateTime.
    //!requests the file modification dates.


    /*!
     \brief

     \return QStringList
    */
    QStringList requestImageNames();

    //! A method taking no arguments and returning a QStringList.
    /*!
     requests a list of the current classifier names stored in the model
      \return list of the current classifier names
    */
    QStringList requestClassifierNames();

    //! A method taking no arguments and returning a QString.
    /*!
     Using QFileDialog the user is presented with the os's file
     explorer only showing directories and is prompted to select
     the folder containing the dataset they want to label. the
     path of the selected folder is returned.
      \return Folder path as a QString.
    */
    QString requestFolderPath();

    //! A method taking no arguments and returning a QString.
    /*!
     Using QFileDialog the user is presented with the os's file
     explorer only showing *.names files and is prompted to select
     their class file. the path of the selected file is returned.
      \return File path as a QString.
    */
    QString requestFilePath();

    //! A method taking 1 argument and returing a QPixmap.
    /*!

    */
    QGraphicsPixmapItem * requestImage(const QString imageName);

    QStringList requestSortedNameAscending(int i);
    //! Sorts either the image or the class names in ascending order.
    //! The int i parameter is used to determine which one is sorted(class or image).

    /*!
     \brief

     \param i
     \return QStringList
    */
    QStringList requestSortedNameDescending(int i);
    //! Same as requestSortedNameAscending, but descending instead.

    /*!
     \brief

     \return QStringList
    */
    QStringList requestSortedDateAscending();
    //! Sorts the image file modified date ascending.

    /*!
     \brief

     \return QStringList
    */
    QStringList requestSortedDateDescending();
    //! Sorts the image file modified date descending.

    /*!
     \brief

     \param v
     \return QStringList
    */
    QStringList vectorToQStringList(std::vector<std::string> v);
    /**
     * @brief
     *
     * @param list
     * @return std::vector<std::string>
     */
    std::vector<std::string> qStringListToVector(QStringList list);

    void pointDrawn();

};

#endif // CONTROL_H
