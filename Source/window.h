#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QMovie>
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
    void OnReset();
    void OnDefaults();
    void OnSave();
    void OnAbout();
    void OnStart();
    void OnCheck(bool);
    void OnStatus();
    void OnParameters();
    void OnDisconnect();
    void OnConnect();
    void OnEditChanged();
    void OnSpinChanged();
    void OnComboChanged();
    void OnCheckChanged();
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
    void getParameters();
    void clearFields();
    void startStop(bool);

private:
    Ui::Window* ui;
    Sensor sensor;
    bool runned;
    QPair<QString, bool> address;
    QPair<QString, bool> port;
    QPair<QString, bool> subnet;
    QPair<QString, bool> gateway;
    QPair<qint16,  bool> startAngle;
    QPair<qint16,  bool> endAngle;
    QPair<qint16,  bool> syncOffset;
    QPair<quint16, bool> scanFrequency;
    QPair<quint16, bool> angularResolution;
    QPair<QPair<bool, bool>, bool> dataFlags;
};

#endif
