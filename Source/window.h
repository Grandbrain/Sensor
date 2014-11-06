#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "sensor.h"
#include "about.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:

    void AboutDialog();
    void Connect();
    void Send();
    void Append(QByteArray);

private:
    Ui::Window *ui;
    Sensor client;
};

#endif
