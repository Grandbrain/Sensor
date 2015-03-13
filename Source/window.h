#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include "sensor.h"

namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget* = 0);
    virtual ~Window();

private slots:
    void OnDisconnect();
    void OnConnect();
    void OnAbout();
    void OnSensorData(const ScanData&);

private:
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::Window* ui;
    Sensor sensor;
};

#endif
