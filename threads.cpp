#include "threads.h"
#include<QtCore>
#include <QtDebug>
#include "control.h"

Threads::Threads(Control *cont, QObject *parent) : QThread(parent){
    control = cont;
}

void Threads::run()
{
    while(1){
        QThread::sleep(60); //60 seconds

        control->requestSave();
        qDebug("saved");
    }
}
