#ifndef MODEL_H
#define MODEL_H

#include "control.h"
#include "imagedata.h"

#include <QStringListModel>

#include <map>

class Model
{
    Control *control;

    std::map<std::string,ImageData> imageData;
    std::vector<std::string> classifierNames;
public:
    Model(Control *cont = nullptr);


    std::vector<std::string> imageNames;
    std::vector<std::string> getImageNames() {return this->imageNames;}
    std::vector<std::string> getClassifierNames() {return imageNames;}

    ~Model();
};

#endif // MODEL_H
