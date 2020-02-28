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
    Control *control; /*!< TODO: describe */
    std::vector<std::string> imageNames; /*!< TODO: describe */
    std::map<std::string, Image * > images; /*!< TODO: describe */
    std::vector<std::string> classifierNames; /*!< TODO: describe */
    std::vector<QDateTime>dates; /*!< TODO: describe */
public:
    /*!
     \brief

     \param cont
    */
    Model(Control *cont = nullptr);

    /*!
     \brief

     \return std::vector<std::string>
    */
    std::vector<std::string> getImageNames() {return imageNames;}
    /*!
     \brief

     \return std::vector<std::string>
    */
    std::vector<std::string> getClassifierNames() {return classifierNames;}
    /*!
     \brief

     \return std::vector<QDateTime>
    */
    std::vector<QDateTime> getDates() {return dates;}

    /*!
     \brief

     \return QMap<std::string, QPen>
    */
    QMap<std::string,QPen> requestPens();
    /*!
     \brief

     \param imageName
     \return QGraphicsPixmapItem
    */
    QGraphicsPixmapItem * requestImageItem(std::string imageName);
    /*!
     \brief

     \return std::string
    */
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
    /*!
     \brief

     \param imageName
    */
    void requestConnectLastDrawnPoints(std::string imageName);
    /*!
     \brief

     \param imageName
    */
    void requestAddDrawnShape(std::string imageName);

    /*!
     \brief

     \param folderPath
     \return std::string
    */
    std::string loadDataset(std::string folderPath);
    /*!
     \brief

     \param filePath
     \return std::string
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
