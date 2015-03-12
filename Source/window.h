#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWheelEvent>

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
    void OnConnect();
    void OnAbout();
    void OnSliderChange(int);
    void OnPlay();

private:
    bool eventFilter(QObject*, QEvent*);
    void scale(int);

private:
    Ui::Window* ui;
    class Sensor* sensor;
};

#endif
