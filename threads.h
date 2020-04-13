#ifndef THREADS_H
#define THREADS_H
#include <QtCore>

class Threads :public QThread
{
    Q_OBJECT

public:
    explicit Threads(QObject *parent = 0);

protected:
    void run();
};

#endif // THREADS_H
