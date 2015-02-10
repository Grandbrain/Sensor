#include "window.h"
#include "about.h"
#include "search.h"
#include "ui_window.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window), played(false)
{
    ui->setupUi(this);
    connect(ui->actionSearch, SIGNAL(triggered()), SLOT(OnConnect()));
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(OnAbout()));
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), SLOT(OnSliderChange(int)));
    connect(ui->buttonPlay, SIGNAL(released()), SLOT(OnPlay()));

    QGraphicsScene* scene;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush redBrush(Qt::red);
    QPen blackpen(Qt::black);
    blackpen.setWidth(6);
    scene->addEllipse(10, 10, 100, 100, blackpen, redBrush);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
}

Window::~Window()
{
    delete ui;
}

void Window::OnConnect()
{
    Search search(this);
    int result = search.exec();
    if(result == QDialog::Rejected) return;
}

void Window::OnData(ScanHeader)
{
}

void Window::OnAbout()
{
    About about(this);
    about.exec();
}

void Window::OnPlay()
{
    QIcon icon;
    if(played) icon.addFile(":/root/play.ico");
    else icon.addFile(":/root/pause.ico");
    played = !played;
    ui->buttonPlay->setIcon(icon);
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
    ui->verticalSlider->blockSignals(true);
    ui->verticalSlider->setValue(ui->verticalSlider->value() + amount);
    ui->verticalSlider->blockSignals(false);
    double scaleIn = 1.08;
    double scaleOut = 1.0 / scaleIn;
    if(amount < 0)
        for(int i = 0; i < abs(amount); i++)
            ui->graphicsView->scale(scaleOut, scaleOut);
    else
        for(int i = 0; i < abs(amount); i++)
            ui->graphicsView->scale(scaleIn, scaleIn);
}

bool Window::eventFilter(QObject* object, QEvent* event)
{
    if(object != ui->graphicsView->viewport()) return false;
    if(event->type() != QEvent::Wheel) return false;

        int value = ui->verticalSlider->value();
        QWheelEvent* wheelEvent = (QWheelEvent*)event;
        if(wheelEvent->delta() > 0)
        {
            if(value < ui->verticalSlider->maximum())
            {
                scale(1);
                //ui->verticalSlider->blockSignals(true);
                //ui->verticalSlider->setValue(value + 1);
                //ui->verticalSlider->blockSignals(false);
            }
        }
        else
        {
            if(value > ui->verticalSlider->minimum())
            {
                scale(-1);
                //ui->verticalSlider->blockSignals(true);
                //ui->verticalSlider->setValue(value - 1);
                //ui->verticalSlider->blockSignals(false);
            }
        }
        return true;
}
