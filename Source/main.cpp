#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    Window w;
    QSplashScreen splash(QPixmap(":/root/splash.png"));
    splash.show();

    QTimer::singleShot(2000, &splash, SLOT(close()));
    QTimer::singleShot(2000, &w, SLOT(show()));

    return a.exec();
}
