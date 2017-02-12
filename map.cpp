#include "map.h"
#include <QtGui>
#include "hroad.h"
#include "vroad.h"

Map::Map(QWidget *parent) : QWidget(parent)
{
    timer = 0;
    seed = QTime().elapsed();
    qsrand(seed++);
}

Map::~Map()
{
    stop();
}

void Map::start(int interval, int speed)
{
    Road *road;
    int speedInterval = qRound(3600.0 / speed);

    crosses += new Cross(200, 200, this);
    crosses += new Cross(400, 200, this);
    crosses += new Cross(200, 350, this);
    crosses += new Cross(400, 350, this);
    crosses += new Cross(600, 350, this);
    crosses += new Cross(400, 500, this);
    crosses += new Cross(600, 500, this);

    road = new HRoad(200, 100, 500, speedInterval, seed++);
    road->addCross(crosses[0]);
    road->addCross(crosses[1]);
    roads += road;

    road = new HRoad(350, 100, 700, speedInterval, seed++);
    road->addCross(crosses[2]);
    road->addCross(crosses[3]);
    road->addCross(crosses[4]);
    roads += road;

    road = new HRoad(500, 25, 775, speedInterval, seed++);
    road->addCross(crosses[5]);
    road->addCross(crosses[6]);
    roads += road;

    road = new VRoad(200, 25, 450, speedInterval, seed++);
    road->addCross(crosses[0]);
    road->addCross(crosses[2]);
    roads += road;

    road = new VRoad(400, 25, 575, speedInterval, seed++);
    road->addCross(crosses[1]);
    road->addCross(crosses[3]);
    road->addCross(crosses[5]);
    roads += road;

    road = new VRoad(600, 100, 575, speedInterval, seed++);
    road->addCross(crosses[4]);
    road->addCross(crosses[6]);
    roads += road;

    for (QList<Road*>::iterator it = roads.begin(); it != roads.end(); ++it)
        (*it)->start();

    timer = startTimer(interval);
}

void Map::stop()
{
    for (QList<Road*>::iterator it = roads.begin(); it != roads.end(); ++it) {
        (*it)->exit();
        (*it)->wait();
        delete *it;
    }

    for (QList<Cross*>::iterator it = crosses.begin(); it != crosses.end(); ++it)
        delete *it;

    roads.clear();
    crosses.clear();

    if (timer != 0) {
        killTimer(timer);
        timer = 0;
    }
}

void Map::timerEvent(QTimerEvent *)
{
    int i = (int)(((double)qrand() / RAND_MAX) * roads.size());
    roads[i]->addCar();
}

void Map::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (QList<Cross*>::iterator it = crosses.begin(); it != crosses.end(); ++it)
        (*it)->draw(painter);

    for (QList<Road*>::iterator it = roads.begin(); it != roads.end(); ++it)
        (*it)->draw(painter);
}
