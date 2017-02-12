#include "road.h"

Road::Road(int interval, unsigned int seed)
{
    this->interval = interval;
    this->seed = seed;
    moveToThread(this);
}

Road::~Road()
{
    for (QList<QRect*>::iterator it = cars.begin(); it != cars.end(); ++it)
        delete *it;
}

void Road::draw(QPainter &painter)
{
    painter.setPen(Qt::SolidLine);
    painter.setBrush(QBrush());
    painter.drawRect(floor);
    painter.setBrush(QBrush(Qt::green));

    mutex.lock();

    for (QList<QRect*>::iterator it = cars.begin(); it != cars.end(); ++it)
        painter.drawRect(**it);

    mutex.unlock();

    painter.setBrush(QBrush());
    painter.setPen(Qt::DashLine);
    painter.drawLine(line);
}

void Road::run()
{
    startTimer(interval);
    exec();
}

void Road::timerEvent(QTimerEvent *)
{
    QList<QRect*>::iterator itCar;

    mutex.lock();
    itCar = cars.begin();

    while (itCar != cars.end()) {
        moveCar(*itCar);

        if ((*itCar)->intersected(floor) != **itCar) {
            delete *itCar;
            itCar = cars.erase(itCar);
            continue;
        }

        for (QList<Cross*>::iterator itCross = crosses.begin(); itCross != crosses.end(); ++itCross)
            if ((*itCross)->test(*itCar))
                break;

        ++itCar;
    }

    mutex.unlock();
}
