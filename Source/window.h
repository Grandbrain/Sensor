#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QDesktopWidget>
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
    Window(QWidget* = 0);
    ~Window();

private slots:
    void OnAbout();
    void OnStart();
    void OnCheck(bool);
    void OnStatus();
    void OnDisconnect();
    void OnConnect();
    void OnSensorData(const ScanData&);
    void OnSensorError();
    void OnSensorConnected();
    void OnSensorDisconnected();
    void OnSensorStatus(const Status&);
    void OnSensorWarnings(const ErrorsWarnings&);
    void OnSensorParameters(const Parameters&);
    void OnSensorFailed(Command);

private:
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::Window* ui;
    Sensor sensor;
};

#endif
