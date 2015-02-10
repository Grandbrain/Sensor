#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) : QDialog(parent), ui(new Ui::About)
{
    setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
}

About::~About()
{
    delete ui;
}
