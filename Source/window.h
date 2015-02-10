#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
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
    ~Window();

private slots:
    void OnConnect();
    void OnData(ScanHeader);
    void OnAbout();
    void OnSliderChange(int);
    void OnPlay();

private:
    bool eventFilter(QObject*, QEvent*);
    void scale(int);

private:
    Ui::Window* ui;
    Sensor sensor;
    bool played;
};

#endif
