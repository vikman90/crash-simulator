#include "hroad.h"

HRoad::HRoad(int y, int xMin, int xMax, int interval, unsigned int seed)
    : Road(interval, seed)
{
    floor.setCoords(xMin, y - 5, xMax, y + 5);
    line.setLine(xMin, y, xMax, y);
}

void HRoad::addCar()
{
    QRect *car = new QRect(0, 0, 4, 3);

    if (((double)qrand() / RAND_MAX) < 0.5) {
        // Desde la izquierda hacia la derecha
        car->moveLeft(line.x1());
        car->moveTop(line.y1() + 2);
    } else {
        // Desde la derecha hacia la izquierda
        car->moveRight(line.x2());
        car->moveBottom(line.y1() - 2);
    }

    mutex.lock();
    cars += car;
    mutex.unlock();
}

void HRoad::moveCar(QRect *car)
{
    if (car->top() > line.y1())
        car->translate(1, 0);
    else
        car->translate(-1, 0);
}
