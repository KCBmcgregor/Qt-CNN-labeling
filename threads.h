#ifndef THREADS_H
#define THREADS_H
#include <QtCore>

class Control;

class Threads :public QThread
{
    Q_OBJECT
    Control *control;

public:
    explicit Threads(Control *cont, QObject *parent = 0);

protected:
    void run();
};

#endif // THREADS_H
