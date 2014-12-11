#include "window.h"
#include "search.h"
#include "ui_window.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(ui->actionSearch, SIGNAL(triggered()), SLOT(OnConnect()));
    connect(&sensor, SIGNAL(Update(ScanHeader)), SLOT(OnData(ScanHeader)));
}

Window::~Window()
{
    delete ui;
}

void Window::OnConnect()
{
    Search search;
    int result = search.exec();
    if(result == QDialog::Rejected) return;

    QString address = search.GetAddress();
    quint16 port = search.GetPort();

    sensor.Connect(address, port);
}

void Window::OnData(ScanHeader header)
{
    qDebug() << "Scan points: " << QString::number(header.ScanPoints);
    qDebug() << "Start angle: " << QString::number(header.EndAngle);
}
