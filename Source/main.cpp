#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/logo/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    Window w;
    QTimer::singleShot(2500, &splash, SLOT(close()));
    QTimer::singleShot(2500, &w, SLOT(show()));
    //w.show();
    return a.exec();
}
