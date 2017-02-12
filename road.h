#ifndef ROAD_H
#define ROAD_H

#include <QThread>
#include <QPainter>
#include <QMutex>
#include <QList>
#include <QRect>
#include <QLine>
#include "cross.h"

class Road : public QThread
{
    Q_OBJECT

public:

    explicit Road(int interval, unsigned int seed);
    ~Road();

    inline void addCross(Cross *cross)
    {
        crosses += cross;
    }

    virtual void addCar() = 0;
    virtual void moveCar(QRect *car) = 0;
    void draw(QPainter &painter);

signals:
    void collision();

protected:
    void run();
    void timerEvent(QTimerEvent *);

    int interval;
    unsigned int seed;
    QRect floor;
    QLine line;
    QList<QRect*> cars;
    QList<Cross*> crosses;
    QMutex mutex;
};

#endif // ROAD_H
