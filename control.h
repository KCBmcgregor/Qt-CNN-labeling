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
    std::string mode;
    int sidesToDraw;

public:
    //! The Contol constructor.
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

    void setMode(std::string m) {mode = m;}
    void setSidesToDraw(QString shape);

    //! A method taking no arguments and returning a QStringList.
    /*!
     requests a list of the current image names stored in the model
      @return list of the current image names
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



    QStringList vectorToQStringList(std::vector<std::string> v);
    /**
     * @brief
     *
     * @param list
     * @return std::vector<std::string>
     */
    std::vector<std::string> qStringListToVector(QStringList list);

};

#endif // CONTROL_H
