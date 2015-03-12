#include <QApplication>
#include <QTimer>
#include "window.h"
#include "splash.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    Splash s;
    s.exec();

    Window w;
    w.show();

    return a.exec();
}
