#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);

    map = new Map(ui.canvas);
    map->resize(800, 600);

    connect(ui.btStart, SIGNAL(clicked()), SLOT(start()));
    connect(ui.btStop, SIGNAL(clicked()), SLOT(stop()));
    connect(map, SIGNAL(collision()), SLOT(collision()));

    startTimer(50);
}

void Widget::start()
{
    int interval = ui.spinInterval->value();
    int speed = ui.spinSpeed->value();
    int falseSpeed;

    ui.spinInterval->setEnabled(false);
    ui.spinSpeed->setEnabled(false);
    ui.rdSimulate->setEnabled(false);
    ui.rdMeasure->setEnabled(false);
    ui.cbLog->setEnabled(false);
    ui.btStart->setEnabled(false);
    ui.btStop->setEnabled(true);
    ui.lcdCollisions->display(0);
    ui.lcdAverage->display(0);

    nCollisions = 0;

    if (ui.rdSimulate->isChecked())
        multiplier = 1.0;
    else {
        falseSpeed = 3600 / qRound((float)(3600 / ui.spFalseSpeed->value()));
        multiplier = (double)falseSpeed / speed;
        interval = qRound(interval / multiplier);
        speed = falseSpeed;
        ui.spFalseSpeed->setEnabled(false);
    }

    map->start(interval, speed);
}

void Widget::stop()
{
    ui.spinInterval->setEnabled(true);
    ui.spinSpeed->setEnabled(true);
    ui.rdSimulate->setEnabled(true);
    ui.rdMeasure->setEnabled(true);
    ui.cbLog->setEnabled(true);
    ui.btStart->setEnabled(true);
    ui.btStop->setEnabled(false);

    if (ui.rdMeasure->isChecked())
        ui.spFalseSpeed->setEnabled(true);

    map->stop();
}

void Widget::collision()
{
    double average;
    nCollisions++;

    if (nCollisions == 1) {
        time.start();
        average = 0.0;
    }
    else if (time.elapsed() == 0)
        average = 0.0;
    else
        average = (nCollisions) / ((multiplier * time.elapsed() / 60000.0));

    ui.lcdCollisions->display(nCollisions);
    ui.lcdAverage->display(average);
}

void Widget::timerEvent(QTimerEvent *)
{
    map->update();
}
