#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include "road.h"
#include "cross.h"

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = 0);
    ~Map();

    void start(int interval, int speed);
    void stop();

signals:
    void collision();

protected:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);

private:
    int timer;
    unsigned int seed;
    QList<Road*> roads;
    QList<Cross*> crosses;
};

#endif // MAP_H
