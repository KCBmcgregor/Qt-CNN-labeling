#ifndef MODEL_H
#define MODEL_H

#include "control.h"

class Model
{
    Control *control;
public:
    Model(Control *cont);
};

#endif // MODEL_H
