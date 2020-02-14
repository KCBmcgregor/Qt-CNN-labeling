#include "model.h"

Model::Model(Control *cont)
{
    control = cont;

    imageNames = {"TestImage_name","TestImage_name_2"};

    imageData = {};

    classifierNames = {"testclass","testclass_2"};

}

Model::~Model()
{
    delete this;
}
