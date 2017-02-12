#ifndef HROAD_H
#define HROAD_H

#include "road.h"

class HRoad : public Road
{
    Q_OBJECT

public:
    HRoad(int y, int xMin, int xMax, int interval, unsigned int seed);

    void addCar();
    void moveCar(QRect *car);
};

#endif // HROAD_H
