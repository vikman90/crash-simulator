#include "cross.h"
#include "map.h"

Cross::Cross(int x, int y, Map *map)
{
    rect.setWidth(10);
    rect.setHeight(10);
    rect.moveCenter(QPoint(x, y));

    connect(this, SIGNAL(collision()), map, SIGNAL(collision()));
}

bool Cross::test(QRect *car)
{
    mutex.lock();

    if (car->intersects(rect)) {
        if (!cars.contains(car))
            cars += car;

        for (QSet<QRect*>::iterator i = cars.begin(); i != cars.end(); ++i) {
            for (QSet<QRect*>::iterator j = cars.begin(); j != cars.end(); ++j) {
                if (i != j && (*i)->intersects(**j)) {
                    if (!(collided.contains(*i) || collided.contains(*j))) {
                        emit collision();
                        collided << *i << *j;
                    }
                }
            }
        }

        mutex.unlock();
        return true;
    }
    else {
        cars -= car;
        collided -= car;
        mutex.unlock();
        return false;
    }
}

void Cross::draw(QPainter &painter)
{
    bool collision;

    mutex.lock();
    collision = !collided.empty();
    mutex.unlock();

    if (collision) {
        painter.setPen(Qt::transparent);
        painter.setBrush(QBrush(Qt::yellow));
        painter.drawEllipse(rect.center(), 20, 20);
    }

    painter.setPen(Qt::SolidPattern);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(rect);
}
