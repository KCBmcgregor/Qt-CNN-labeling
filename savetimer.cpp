#include "savetimer.h"
#include<QtCore>
#include <QtDebug>

saveTimer::saveTimer()
{
timer = new QTimer (this);
connect (timer,SIGNAL(timeout()),this,SLOT(MySlot()));
timer->start(1000);

}

void saveTimer::MySlot(){
    int counter=0;
    qDebug()<<"Timer has been executed";
    counter ++;
           if(counter==60){
            //add saving implementation
                counter = 0;
           }
}
