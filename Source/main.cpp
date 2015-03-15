#include <QApplication>
#include <QTranslator>
#include "window.h"
#include "splash.h"

void translate()
{
    QLocale currentLocale = QLocale::system();
    if(currentLocale.language() != QLocale::Language::English) return;
    QStringList files {"", ""};
    foreach (QString file, files)
    {
        QTranslator* translator = new QTranslator(qApp);
        translator->load(file);
        qApp->installTranslator(translator);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    translate();

    Splash s;
    s.exec();

    Window w;
    w.show();

    return a.exec();
}
