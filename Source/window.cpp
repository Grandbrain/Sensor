#include "window.h"
#include "ui_window.h"
#include "about.h"

Window::Window(QWidget* parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    //ui->progressBar->hide();
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(OnAbout()));
}

Window::~Window()
{
    delete ui;
}

void Window::OnConnect()
{
}

void Window::OnDisconnect()
{

}

void Window::OnSensorData(const ScanData& data)
{
    QGraphicsScene* scene = ui->graphicsView->scene();
    scene->clear();

    QPen cyan(QColor(Qt::cyan), 2);
    QPen redEcho0(QColor(139, 0, 0), 2);
    QPen redEcho1(QColor(205, 0, 0), 1);
    QPen redEcho2(QColor(238, 0, 0), 1);
    QPen redEcho3(QColor(255, 0, 0), 1);
    QPen blueEcho0(QColor(0, 0, 139), 1);
    QPen blueEcho1(QColor(0, 0, 205), 1);
    QPen blueEcho2(QColor(0, 0, 238), 1);
    QPen blueEcho3(QColor(0, 0, 255), 1);
    QPen greenEcho0(QColor(0, 139, 0), 1);
    QPen greenEcho1(QColor(0, 205, 0), 1);
    QPen greenEcho2(QColor(0, 238, 0), 1);
    QPen greenEcho3(QColor(0, 255, 0), 1);
    QPen yellowEcho0(QColor(139, 139, 0), 1);
    QPen yellowEcho1(QColor(205, 205, 0), 1);
    QPen yellowEcho2(QColor(238, 238, 0), 1);
    QPen yellowEcho3(QColor(255, 255, 0), 1);
    QBrush white(QColor(255, 255, 255));

    foreach (Point point, data.Points)
    {
        scene->addLine(0, 480, 640, 480, cyan);
        scene->addLine(320, 0, 320, 480, cyan);
        qreal x = 320 - point.RadialDistance * qSin(point.HorizontalAngle);
        qreal y = 480 - point.RadialDistance * qCos(point.HorizontalAngle);
        if(point.Layer == 0)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, redEcho0, white);
                scene->addLine(320, 480, x, y, redEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, redEcho1, white);
                scene->addLine(320, 480, x, y, redEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, redEcho2, white);
                scene->addLine(320, 480, x, y, redEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, redEcho3, white);
                scene->addLine(320, 480, x, y, redEcho3);
            }
        }
        if(point.Layer == 1)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho0, white);
                scene->addLine(320, 480, x, y, blueEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho1, white);
                scene->addLine(320, 480, x, y, blueEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho2, white);
                scene->addLine(320, 480, x, y, blueEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho3, white);
                scene->addLine(320, 480, x, y, blueEcho3);
            }
        }
        if(point.Layer == 2)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho0, white);
                scene->addLine(320, 480, x, y, greenEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho1, white);
                scene->addLine(320, 480, x, y, greenEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho2, white);
                scene->addLine(320, 480, x, y, greenEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho3, white);
                scene->addLine(320, 480, x, y, greenEcho3);
            }
        }
        if(point.Layer == 3)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho0, white);
                scene->addLine(320, 480, x, y, yellowEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho1, white);
                scene->addLine(320, 480, x, y, yellowEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho2, white);
                scene->addLine(320, 480, x, y, yellowEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho3, white);
                scene->addLine(320, 480, x, y, yellowEcho3);
            }
        }
    }
}

void Window::OnAbout()
{
    About about(this);
    about.exec();
}

bool Window::eventFilter(QObject* object, QEvent* event)
{
    if(object != ui->graphicsView->viewport()) return false;
    if(event->type() != QEvent::Wheel) return false;
    double in = 1.08, out = 1.0 / in;
    QWheelEvent* wheel = (QWheelEvent*)event;
    if(wheel->delta() > 0) ui->graphicsView->scale(in, in);
    else ui->graphicsView->scale(out, out);
    return true;
}
