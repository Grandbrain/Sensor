#include "splash.h"
#include "ui_splash.h"

Splash::Splash(QWidget* parent) : QDialog(parent), ui(new Ui::Splash)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);
    QTimer::singleShot(2000, this, SLOT(close()));
}

Splash::~Splash()
{
    delete ui;
}
