#include "splash.h"
#include "ui_splash.h"

Splash::Splash(QWidget *parent) : QWidget(parent), ui(new Ui::Splash)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QPixmap(":/root/splash.png")));
    setPalette(palette);
    setAutoFillBackground(true);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);
}

Splash::~Splash()
{
    delete ui;
}
