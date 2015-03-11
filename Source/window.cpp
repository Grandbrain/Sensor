#include "window.h"
#include "about.h"
#include "ui_window.h"
#include <QMessageBox>

Window::Window(QWidget* parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    connect(ui->actionConnect, SIGNAL(triggered()), SLOT(OnConnect()));
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(OnAbout()));
    connect(ui->slider, SIGNAL(valueChanged(int)), SLOT(OnSliderChange(int)));
    connect(ui->buttonPlay, SIGNAL(released()), SLOT(OnPlay()));
}

Window::~Window()
{
    delete ui;
}

void Window::OnConnect()
{
    Connect c(nullptr, this);
    c.exec();
}

void Window::OnAbout()
{
    About about(this);
    about.exec();
}

void Window::OnPlay()
{
}

void Window::OnSliderChange(int value)
{
    static int oldValue = 0;
    int delta = value - oldValue;
    oldValue = value;
    scale(delta);
}

void Window::scale(int amount)
{
    ui->slider->blockSignals(true);
    ui->slider->setValue(ui->slider->value() + amount);
    ui->slider->blockSignals(false);
    double scaleIn = 1.08;
    double scaleOut = 1.0 / scaleIn;
    if(amount < 0)
        for(int i = 0; i < abs(amount); i++)
            ui->graphicsView->scale(scaleOut, scaleOut);
    else
        for(int i = 0; i < abs(amount); i++)
            ui->graphicsView->scale(scaleIn, scaleIn);
}

void Window::mousePressEvent(QMouseEvent* event)
{
    //if(ui->lineEdit_5->rect().contains(ui->lineEdit_5->mapFromGlobal(QCursor::pos())))
        QMessageBox::information(this, "Mouse event", "Line edit 5!");
}

bool Window::eventFilter(QObject* object, QEvent* event)
{
    if(object != ui->graphicsView->viewport()) return false;
    if(event->type() != QEvent::Wheel) return false;
    int value = ui->slider->value();
    QWheelEvent* wheel = (QWheelEvent*)event;
    if(wheel->delta() > 0) { if(value < ui->slider->maximum()) scale(1); }
    else if(value > ui->slider->minimum()) scale(-1);
    return true;
}


/*QGraphicsScene* scene;
scene = new QGraphicsScene(this);
ui->graphicsView->setScene(scene);
QBrush redBrush(Qt::red);
QPen blackpen(Qt::black);
blackpen.setWidth(6);
scene->addEllipse(10, 10, 100, 100, blackpen, redBrush);
ui->graphicsView->viewport()->installEventFilter(this);
ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);*/
