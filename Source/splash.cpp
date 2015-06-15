#include "splash.h"
#include "ui_splash.h"

Splash::Splash(QWidget* parent) : QDialog(parent), ui(new Ui::Splash)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);
    QRect rect = qApp->desktop()->availableGeometry();
    int sWidth = rect.width();
    int sHeight = rect.height();
    int width = QDialog::width();
    int height = QDialog::height();
    setGeometry((sWidth/2)-(width/2),(sHeight/2)-(height/2),width,height);
    QTimer::singleShot(2000, this, SLOT(close()));
}

Splash::~Splash()
{
    delete ui;
}
