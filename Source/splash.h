#ifndef SPLASH_H
#define SPLASH_H

#include <QApplication>
#include <QDesktopWidget>
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
    explicit Splash(QWidget* = 0);
    virtual ~Splash();

private:
    Ui::Splash *ui;
};

#endif
