#include "threads.h"
#include<QtCore>
#include <QtDebug>

Threads::Threads(QObject *parent) : QThread(parent){}

void Threads::run()
{
    while(1){
        QThread::sleep(60); //60 seconds

        //SLOT(requestSave()); or control->requestSave();
        //qDebug("saved");
    }
}
