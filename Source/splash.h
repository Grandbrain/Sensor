#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>

namespace Ui
{
    class Splash;
}

class Splash : public QWidget
{
    Q_OBJECT

public:
    explicit Splash(QWidget* = 0);
    virtual ~Splash();

private:
    Ui::Splash *ui;
};

#endif
