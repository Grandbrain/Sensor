#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(&client, SIGNAL(Update(QByteArray)), this, SLOT(Append(QByteArray)));
}

Window::~Window()
{
    delete ui;
}

void Window::Connect()
{
    QString title = "Connection status";
    QString host = "stackoverflow.com";
    quint16 port = 80;
    client.Connect(host, port);
    if(client.Connected())
        QMessageBox::information(this, title, "Successful connection to " + host);
    else QMessageBox::critical(this, title, "Unable to connect to the host " + host);
}

void Window::Send()
{
    QByteArray array;
    array.append("GET / HTTP/1.1\n");
    array.append("Host: stackoverflow.com\n");
    array.append("\n");
    if(client.Send(array))
        QMessageBox::information(this, "Sending status", "Data has been successfully sent!");
    else QMessageBox::critical(this, "Sending status", "The data was not sent!");
}

void Window::Append(QByteArray)
{

}
