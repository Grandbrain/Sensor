#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>
#include "sensor.h"

namespace Ui
{
    class Connect;
}

class Connect : public QDialog
{
    Q_OBJECT

public:
    explicit Connect(Sensor*, QWidget* = 0);
    virtual ~Connect();

private slots:
    void OnConnecting();
    void OnDisconnecting();
    void OnConnected();
    void OnDisconnected();
    void OnError();

private:
    Ui::Connect* ui;
    Sensor* sensor;
};

#endif
