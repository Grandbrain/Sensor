#include "window.h"
#include "ui_window.h"
#include "about.h"

Window::Window(QWidget* parent) : QMainWindow(parent), ui(new Ui::Window)
{
    QString range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp regex ("^" + range + "\\." + range + "\\." + range + "\\." + range + "$");
    QValidator* addressValidator = new QRegExpValidator(regex, this);
    QValidator* portValidator = new QIntValidator(0, 65535, this);
    installEventFilter(this);

    ui->setupUi(this);
    ui->progressConnection->hide();
    ui->widgetMessage->hide();
    //ui->tabWidget->setTabEnabled(1, false);
    //ui->tabWidget->setTabEnabled(2, false);
    ui->editConnectionAddress->setValidator(addressValidator);
    ui->editConnectionPort->setValidator(portValidator);
    ui->widgetMessage->installEventFilter(this);
    ui->editAddress->setValidator(addressValidator);
    ui->editPort->setValidator(portValidator);
    ui->editSubnet->setValidator(addressValidator);
    ui->editGateway->setValidator(addressValidator);
    ui->spinStartAngle->setMaximum(sensor.GetStartAngleBoundary().second);
    ui->spinStartAngle->setMinimum(sensor.GetStartAngleBoundary().first);
    ui->spinEndAngle->setMaximum(sensor.GetEndAngleBoundary().second);
    ui->spinEndAngle->setMinimum(sensor.GetEndAngleBoundary().first);
    ui->spinSyncOffset->setMinimum(sensor.GetSyncAngleBoundary().first);
    ui->spinSyncOffset->setMaximum(sensor.GetSyncAngleBoundary().second);
    foreach (quint16 value, sensor.GetScanFrequencyValues())
        ui->comboScanFrequency->addItem(QString::number(value));
    foreach (quint16 value, sensor.GetAngularResolutionValues())
        ui->comboAngularResolution->addItem(QString::number(value));
    ui->lineParameters->hide();
    ui->progressParameters->hide();
    ui->lineStatus->hide();
    ui->progressStatus->hide();

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->installEventFilter(this);

    connect(ui->checkExternalSync, SIGNAL(clicked(bool)), SLOT(OnCheck(bool)));
    connect(ui->checkFrequencyLocked, SIGNAL(clicked(bool)), SLOT(OnCheck(bool)));
    connect(ui->checkLaserOn, SIGNAL(clicked(bool)), SLOT(OnCheck(bool)));
    connect(ui->checkMotorOn, SIGNAL(clicked(bool)), SLOT(OnCheck(bool)));
    connect(ui->checkPhaseLocked, SIGNAL(clicked(bool)), SLOT(OnCheck(bool)));
    connect(ui->buttonStatus, SIGNAL(released()), SLOT(OnStatus()));
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(OnAbout()));
    connect(ui->buttonConnect, SIGNAL(released()), SLOT(OnConnect()));
    connect(ui->buttonDisconnect, SIGNAL(released()), SLOT(OnDisconnect()));
    connect(&sensor, SIGNAL(OnError()), SLOT(OnSensorError()));
    connect(&sensor, SIGNAL(OnConnected()), SLOT(OnSensorConnected()));
    connect(&sensor, SIGNAL(OnDisconnected()), SLOT(OnSensorDisconnected()));
    connect(&sensor, SIGNAL(OnPoints(ScanData)), SLOT(OnSensorData(ScanData)));
    connect(&sensor, SIGNAL(OnStatus(Status)), SLOT(OnSensorStatus(Status)));
    connect(&sensor, SIGNAL(OnWarnings(ErrorsWarnings)), SLOT(OnSensorWarnings(ErrorsWarnings)));
    connect(&sensor, SIGNAL(OnFailed(Command)), SLOT(OnSensorFailed(Command)));
    connect(&sensor, SIGNAL(OnParameters(Parameters)), SLOT(OnSensorParameters(Parameters)));
}

Window::~Window()
{
    delete ui;
}

void Window::OnAbout()
{
    About about(this);
    about.exec();
}

void Window::OnCheck(bool checked)
{
    if(checked && sender() == ui->checkExternalSync)
        ui->checkExternalSync->setChecked(false);
    if(checked && sender() == ui->checkFrequencyLocked)
        ui->checkFrequencyLocked->setChecked(false);
    if(checked && sender() == ui->checkLaserOn)
        ui->checkLaserOn->setChecked(false);
    if(checked && sender() == ui->checkMotorOn)
        ui->checkMotorOn->setChecked(false);
    if(checked && sender() == ui->checkPhaseLocked)
        ui->checkPhaseLocked->setChecked(false);
    if(!checked && sender() == ui->checkExternalSync)
        ui->checkExternalSync->setChecked(true);
    if(!checked && sender() == ui->checkFrequencyLocked)
        ui->checkFrequencyLocked->setChecked(true);
    if(!checked && sender() == ui->checkLaserOn)
        ui->checkLaserOn->setChecked(true);
    if(!checked && sender() == ui->checkMotorOn)
        ui->checkMotorOn->setChecked(true);
    if(!checked && sender() == ui->checkPhaseLocked)
        ui->checkPhaseLocked->setChecked(true);
}

void Window::OnSensorConnected()
{
    ui->progressConnection->hide();
    ui->buttonConnect->setEnabled(false);
    ui->buttonDisconnect->setEnabled(true);
    ui->buttonDisconnect->setDefault(true);
    ui->editConnectionAddress->setEnabled(false);
    ui->editConnectionPort->setEnabled(false);
    ui->tabWidget->setTabEnabled(1, true);
    ui->tabWidget->setTabEnabled(2, true);
    ui->widgetMessage->show();
    QTimer::singleShot(30000, ui->widgetMessage, SLOT(hide()));
}

void Window::OnSensorDisconnected()
{
    ui->widgetMessage->hide();
    ui->progressConnection->hide();
    ui->buttonConnect->setEnabled(true);
    ui->buttonDisconnect->setEnabled(false);
    ui->buttonConnect->setDefault(true);
    ui->editConnectionAddress->setEnabled(true);
    ui->editConnectionPort->setEnabled(true);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
}

void Window::OnSensorError()
{
    if(ui->progressConnection->isVisible())
    {
        if(ui->editConnectionAddress->isEnabled())
        {
            ui->progressConnection->hide();
            ui->labelConnectionMessage->setText(tr("Не удалось выполнить подключение."));
            ui->labelConnectionResult->setPixmap(QPixmap(":/root/Resources/error.ico"));
            ui->widgetMessage->setStyleSheet(".QWidget { border: 2px solid #C22B31; background-color: rgb(242, 213, 213); }");
            ui->buttonConnect->setEnabled(true);
            ui->widgetMessage->show();
            QTimer::singleShot(30000, ui->widgetMessage, SLOT(hide()));
        }
        else
        {
            ui->progressConnection->hide();
            ui->labelConnectionMessage->setText(tr("Не удалось отключиться."));
            ui->labelConnectionResult->setPixmap(QPixmap(":/root/Resources/error.ico"));
            ui->widgetMessage->setStyleSheet(".QWidget { border: 2px solid #C22B31; background-color: rgb(242, 213, 213); }");
            ui->buttonDisconnect->setEnabled(true);
            ui->widgetMessage->show();
            QTimer::singleShot(30000, ui->widgetMessage, SLOT(hide()));
        }
    }
}

void Window::OnConnect()
{
    ui->widgetMessage->hide();
    QString address = ui->editConnectionAddress->text();
    QString port = ui->editConnectionPort->text();
    if(address.isEmpty() || port.isEmpty()) return;
    ui->progressConnection->show();
    ui->buttonConnect->setEnabled(false);
    sensor.Connect(address, port.toUShort());
}

void Window::OnDisconnect()
{
    ui->widgetMessage->hide();
    ui->progressConnection->show();
    ui->buttonDisconnect->setEnabled(false);
    sensor.Disconnect();
}

void Window::OnStatus()
{
    sensor.GetStatus();
}

void Window::OnSensorStatus(const Status& status)
{
    ui->checkExternalSync->blockSignals(true);
    ui->checkFrequencyLocked->blockSignals(true);
    ui->checkLaserOn->blockSignals(true);
    ui->checkMotorOn->blockSignals(true);
    ui->checkPhaseLocked->blockSignals(true);
    ui->editFirmwareVersion->setText(status.FirmwareVersion);
    ui->editFPGAVersion->setText(status.FPGAVersion);
    ui->editTemperature->setText(QString::number(status.Temperature));
    ui->editSerialNumber->setText(status.SerialNumber);
    ui->editFPGA->setText(status.FPGATime);
    ui->editDSP->setText(status.DSPTime);
    ui->editAngleTicks->setText(QString::number(sensor.GetAngleTicksPerRotation()));
    ui->checkExternalSync->setChecked(status.ExternalSyncSignal);
    ui->checkFrequencyLocked->setChecked(status.FrequencyLocked);
    ui->checkLaserOn->setChecked(status.LaserOn);
    ui->checkMotorOn->setChecked(status.MotorOn);
    ui->checkPhaseLocked->setChecked(status.PhaseLocked);
    ui->checkExternalSync->blockSignals(false);
    ui->checkFrequencyLocked->blockSignals(false);
    ui->checkLaserOn->blockSignals(false);
    ui->checkMotorOn->blockSignals(false);
    ui->checkPhaseLocked->blockSignals(false);
}

void Window::OnSensorData(const ScanData& data)
{
    QGraphicsScene* scene = ui->graphicsView->scene();
    scene->clear();

    QPen cyan(QColor(Qt::cyan), 2);
    QPen redEcho0(QColor(139, 0, 0), 2);
    QPen redEcho1(QColor(205, 0, 0), 2);
    QPen redEcho2(QColor(238, 0, 0), 2);
    QPen redEcho3(QColor(255, 0, 0), 2);
    QPen blueEcho0(QColor(0, 0, 139), 2);
    QPen blueEcho1(QColor(0, 0, 205), 2);
    QPen blueEcho2(QColor(0, 0, 238), 2);
    QPen blueEcho3(QColor(0, 0, 255), 2);
    QPen greenEcho0(QColor(0, 139, 0), 2);
    QPen greenEcho1(QColor(0, 205, 0), 2);
    QPen greenEcho2(QColor(0, 238, 0), 2);
    QPen greenEcho3(QColor(0, 255, 0), 2);
    QPen yellowEcho0(QColor(139, 139, 0), 2);
    QPen yellowEcho1(QColor(205, 205, 0), 2);
    QPen yellowEcho2(QColor(238, 238, 0), 2);
    QPen yellowEcho3(QColor(255, 255, 0), 2);
    QBrush white(QColor(255, 255, 255));

    foreach (Point point, data.Points)
    {
        scene->addLine(0, 480, 640, 480, cyan);
        scene->addLine(320, 0, 320, 480, cyan);
        qreal x = 320 - point.RadialDistance * sin(point.HorizontalAngle);
        qreal y = 480 - point.RadialDistance * cos(point.HorizontalAngle);
        if(point.Layer == 0)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, redEcho0, white);
                scene->addLine(320, 480, x, y, redEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, redEcho1, white);
                scene->addLine(320, 480, x, y, redEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, redEcho2, white);
                scene->addLine(320, 480, x, y, redEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, redEcho3, white);
                scene->addLine(320, 480, x, y, redEcho3);
            }
        }
        if(point.Layer == 1)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho0, white);
                scene->addLine(320, 480, x, y, blueEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho1, white);
                scene->addLine(320, 480, x, y, blueEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho2, white);
                scene->addLine(320, 480, x, y, blueEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, blueEcho3, white);
                scene->addLine(320, 480, x, y, blueEcho3);
            }
        }
        if(point.Layer == 2)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho0, white);
                scene->addLine(320, 480, x, y, greenEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho1, white);
                scene->addLine(320, 480, x, y, greenEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho2, white);
                scene->addLine(320, 480, x, y, greenEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, greenEcho3, white);
                scene->addLine(320, 480, x, y, greenEcho3);
            }
        }
        if(point.Layer == 3)
        {
            if(point.Echo == 0)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho0, white);
                scene->addLine(320, 480, x, y, yellowEcho0);
            }
            if(point.Echo == 1)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho1, white);
                scene->addLine(320, 480, x, y, yellowEcho1);
            }
            if(point.Echo == 2)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho2, white);
                scene->addLine(320, 480, x, y, yellowEcho2);
            }
            if(point.Echo == 3)
            {
                scene->addEllipse(x, y, 2, 2, yellowEcho3, white);
                scene->addLine(320, 480, x, y, yellowEcho3);
            }
        }
    }
}

void Window::OnSensorWarnings(const ErrorsWarnings& warnings)
{

}

void Window::OnSensorParameters(const Parameters& parameters)
{

}

void Window::OnSensorFailed(Command command)
{

}

bool Window::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return))
        {
            if(ui->buttonConnect->isEnabled()) ui->buttonConnect->click();
            else ui->buttonDisconnect->click();
        }
    }
    if(object == ui->widgetMessage ||
       object == ui->labelConnectionMessage ||
       object == ui->labelConnectionResult)
    {
        if(event->type() == QEvent::MouseButtonRelease)
            ui->widgetMessage->hide();
    }
    if(object != ui->graphicsView) return false;
    if(event->type() != QEvent::Wheel) return false;
    double in = 1.08, out = 1.0 / in;
    QWheelEvent* wheel = (QWheelEvent*)event;
    if(wheel->delta() > 0) ui->graphicsView->scale(in, in);
    else ui->graphicsView->scale(out, out);
    return true;
}
