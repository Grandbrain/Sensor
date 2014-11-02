#include "window.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/logo/logo.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    Window w;
    w.show();
    return a.exec();
}
