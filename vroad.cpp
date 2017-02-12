#include "vroad.h"

VRoad::VRoad(int x, int yMin, int yMax, int interval, unsigned int seed)
    : Road(interval, seed)
{
    floor.setCoords(x - 5, yMin, x + 5, yMax);
    line.setLine(x, yMin, x, yMax);
}

void VRoad::addCar()
{
    QRect *car = new QRect(0, 0, 3, 4);

    if (((double)qrand() / RAND_MAX) < 0.5) {
        // Desde arriba hacia abajo
        car->moveTop(line.y1());
        car->moveRight(line.x1() - 2);
    } else {
        // Desde abajo hacia arriba
        car->moveBottom(line.y2());
        car->moveLeft(line.x1() + 2);
    }

    mutex.lock();
    cars += car;
    mutex.unlock();
}

void VRoad::moveCar(QRect *car)
{
    if (car->right() < line.x1())
        car->translate(0, 1);
    else
        car->translate(0, -1);
}
