#include "splash.h"
#include "ui_splash.h"

Splash::Splash(QWidget* parent) : QDialog(parent), ui(new Ui::Splash)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);
    QRect rect = qApp->desktop()->availableGeometry();
    int w = rect.width();
    int h = rect.height();
    int dw = width();
    int dh = height();
    setGeometry((w / 2) - (dw / 2), (h / 2) - (dh / 2), dw, dh);
    QTimer::singleShot(2000, this, SLOT(close()));
}

Splash::~Splash()
{
    delete ui;
}
