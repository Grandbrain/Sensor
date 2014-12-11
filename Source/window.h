#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "sensor.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget* = 0);
    ~Window();

private slots:
    void OnConnect();
    void OnData(ScanHeader);

private:
    Ui::Window* ui;
    Sensor sensor;
};

#endif
