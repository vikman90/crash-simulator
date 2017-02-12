#ifndef CROSS_H
#define CROSS_H

#include <QObject>
#include <QSet>
#include <QRect>
#include <QMutex>
#include <QPainter>

class Map;

class Cross : QObject
{
    Q_OBJECT

public:
    Cross(int x, int y, Map *map);

    bool test(QRect *car);
    void draw(QPainter &painter);

signals:
    void collision();

private:
    QRect rect;
    QSet<QRect*> cars;
    QSet<QRect*> collided;
    QMutex mutex;
};

#endif // CROSS_H
