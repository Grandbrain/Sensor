#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Window w;
    w.show();
    return a.exec();
}
