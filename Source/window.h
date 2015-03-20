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
    void OnStatus();
    void OnDisconnect();
    void OnConnect();
    void OnAbout();
    void OnSensorData(const ScanData&);
    void OnSensorError();
    void OnSensorConnected();
    void OnSensorDisconnected();
    void OnSensorStatus(const Status&);

private:
    bool eventFilter(QObject*, QEvent*);
    void closeEvent(QCloseEvent*);
    void changeEvent(QEvent*);
    void resizeEvent(QResizeEvent*);
    void ReadSettings();
    void WriteSettings();

private:
    Ui::Window* ui;
    QSettings settings;
    QSize normal;
    Sensor sensor;
};

#endif
