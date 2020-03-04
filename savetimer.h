#ifndef TIMER_H
#define TIMER_H
#include <QtCore>

class saveTimer :public QObject
{
    Q_OBJECT
public:
    saveTimer();
    QTimer *timer;
public slots:
    void MySlot();
};

#endif // TIMER_H
