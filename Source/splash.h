#ifndef SPLASH_H
#define SPLASH_H

#include <QDialog>
#include <QTimer>

namespace Ui
{
    class Splash;
}

class Splash : public QDialog
{
    Q_OBJECT

public:
    Splash(QWidget* = 0);
    ~Splash();

private:
    Ui::Splash *ui;
};

#endif
