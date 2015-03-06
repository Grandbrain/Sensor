#include "connect.h"
#include "ui_connect.h"

Connect::Connect(QWidget *parent) : QDialog(parent), ui(new Ui::Connect)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
}

Connect::~Connect()
{
    delete ui;
}
