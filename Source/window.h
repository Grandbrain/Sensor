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
    void OnStart();
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
    void OnSensorParameters(const Parameters&);
    void OnSensorFailed(Command);

private:
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::Window* ui;
    Sensor sensor;
    bool stopped;
};

#endif
