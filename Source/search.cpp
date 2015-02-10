#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) : QDialog(parent), ui(new Ui::Search)
{
    setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
}

Search::~Search()
{
    delete ui;
}

QString Search::GetAddress() const
{
    return ui->editAddress->text();
}

quint16 Search::GetPort() const
{
    return ui->editPort->text().toUShort();
}
