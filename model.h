#ifndef MODEL_H
#define MODEL_H

#include "control.h"


#include <QStringListModel>

#include <map>

class Image;

/*!
 \brief

*/
class Model
{
    Control *control;


    std::vector<std::string> imageNames;
    //!A public function
    /*!
     * Maps the images.
     */
    std::map<std::string, Image * > images;

    std::vector<std::string> classifierNames;
    //!A public function
    /*!
     * Gets and returns the image dates in ascending order into imageNamesDatesAsc.
     */
    std::vector<std::string> imageNameDatesAsc;

    std::vector<std::string> imageNameDatesDec;
public:
    /*!
     \brief

     \param cont
    */
    Model(Control *cont = nullptr);
    //! A public function
    /*!
     *Gets and returns the image names into imageNames.
     */
    std::vector<std::string> getImageNames() {return imageNames;}
    //!A public function
    /*!
     * Gets and returns the classifier names into classifierNames.
     */
    std::vector<std::string> getClassifierNames() {return classifierNames;}
    //!A public function
    /*!
     * Gets and returns the image dates in decending order into imageNamesDatesDec.
     */
    std::vector<std::string> getImageNameDatesAsc() {return imageNameDatesAsc;}
    //!A public function
    /*!
     * Gets and returns the image names into imageNames.
     */
    std::vector<std::string> getImageNameDatesDec() {return imageNameDatesDec;}

    //!A list of all pens
    /*!
    The QMap is an access method used to retrieve data it stores a list of all pen objects; line, shape, .appoint to be used when drawing shapes
    */
    QMap<std::string,QPen> requestPens();

    QGraphicsPixmapItem * requestImageItem(std::string imageName);

    std::string requestMode();
    /*!
     \brief

     \return std::string
    */
    std::string requestMode2();
    /*!
     \brief

     \return std::string
    */
    std::string requestMode3();
    //!A public function
    /*!
     * Makes a request to attempt connecting the last drawn points, if successful it will connect them.
     * \param imageName
     */
    void requestConnectLastDrawnPoints(std::string imageName);
    //!A public function
    /*!
     * Makes a request to attempt to add a drawn shape,if successful it will draw the shape.
     * \param imageName
     */
    void requestAddDrawnShape(std::string imageName);
    //!A public function
    /*!
     * Loads the dataset into the program and gui, also enables the ability to sort in ascending or decending order.
     * \param folderPath
     *
     */
    std::string loadDataset(std::string folderPath);
    //!A public function
    /*!
     * Loads the classifiers into the program.
     * \param filePath
     *
     */
    std::string loadClassifers(std::string filePath);
    /*!
     \brief

     \param imagePath
     \param imageName
    */
    void loadImage(QString imagePath, const QString imageName);
    /*!
     \brief

     \param imageNames
     \return std::vector<QDateTime>
    */
    std::vector<QDateTime>loadDates(std::vector<std::string> imageNames);
    /*!
     \brief

     \param imagePath
     \return QPixmap
    */
    QPixmap loadImage(const QString imagePath);

    /*!
     \brief

    */
    void pointDrawn() {control->pointDrawn();}






    /*!
     \brief

    */
    ~Model();
};

#endif // MODEL_H
