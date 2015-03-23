#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QDesktopWidget>
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
    void OnCheck(bool);
    void OnStatus();
    void OnDisconnect();
    void OnConnect();
    void OnAbout();
    void OnSensorData(const ScanData&);
    void OnSensorError();
    void OnSensorConnected();
    void OnSensorDisconnected();
    void OnSensorStatus(const Status&);
    void OnSensorWarnings(const ErrorsWarnings&);

private:
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::Window* ui;
    Sensor sensor;
};

#endif
