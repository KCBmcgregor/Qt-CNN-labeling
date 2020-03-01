#include <Qtest>
#include<QtCore>
#include <QtDebug>

class saveTimer :public QObject
{
    Q_OBJECT
public:
    saveTimer();
    QTimer *timer;
public slots:
    void MySlot();
};



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


QTEST_APPLESS_MAIN(saveTimer)

#include "tst_testcasecontrol.moc"
