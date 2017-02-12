#ifndef WIDGET_H
#define WIDGET_H

#include "ui_widget.h"
#include <QTime>
#include "map.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

public slots:
    void start();
    void stop();
    void collision();

protected:
    void timerEvent(QTimerEvent *);

private:
    int nCollisions;
    double multiplier;
    Ui::Widget ui;
    QTime time;
    Map *map;
};

#endif // WIDGET_H
