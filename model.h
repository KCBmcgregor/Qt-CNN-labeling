#ifndef MODEL_H
#define MODEL_H

#include "control.h"

class Model
{
    Control *control;
public:
    Model(Control *cont = nullptr);
};

#endif // MODEL_H
