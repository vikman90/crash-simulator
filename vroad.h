#ifndef VROAD_H
#define VROAD_H

#include "road.h"

class VRoad : public Road
{
    Q_OBJECT

public:
    VRoad(int x, int yMin, int yMax, int interval, unsigned int seed);

    void addCar();
    void moveCar(QRect *car);
};

#endif // VROAD_H
