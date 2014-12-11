#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
}

Search::~Search()
{
    delete ui;
}

QString Search::GetAddress() const
{
    return ui->addressEdit->text();
}

quint16 Search::GetPort() const
{
    return ui->portEdit->text().toUShort();
}
