#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen splash(QPixmap(":/crash.png"), Qt::WindowStaysOnTopHint);
    QTimer::singleShot(2500, &splash, SLOT(close()));
    splash.show();
    app.processEvents();

    Widget widget;
    widget.show();
    return app.exec();
}
