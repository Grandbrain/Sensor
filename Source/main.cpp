#include <QApplication>
#include <QTimer>
#include "splash.h"
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Window w;
    Splash splash;
    splash.show();

    QTimer::singleShot(2000, &splash, SLOT(close()));
    QTimer::singleShot(2000, &w, SLOT(show()));

    return a.exec();
}
