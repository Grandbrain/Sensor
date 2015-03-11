#include "connect.h"
#include "ui_connect.h"

Connect::Connect(Sensor* s, QWidget* p) : QDialog(p), ui(new Ui::Connect)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    if(!s) return;
    sensor = s;
    if(sensor->Connected())
    {
        ui->buttonConnect->setEnabled(false);
        ui->editAddress->setEnabled(false);
        ui->editPort->setEnabled(false);
    }
    else
    {
        ui->buttonDisconnect->setEnabled(false);
    }
}

Connect::~Connect()
{
    delete ui;
}

void Connect::OnConnecting()
{

}

void Connect::OnDisconnecting()
{

}

void Connect::OnConnected()
{

}

void Connect::OnDisconnected()
{

}

void Connect::OnError()
{

}
