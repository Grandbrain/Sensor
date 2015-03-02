#ifndef SENSOR_H
#define SENSOR_H

#include <QtNetwork>
#include <QByteArray>
#include <QtEndian>
#include <QtGlobal>
#include <QString>

#pragma pack(push, 1)
struct DataHeader
{
    quint32     MagicWord           ;
    quint32     PreviousSize        ;
    quint32     Size                ;
    quint8      Reserved            ;
    quint8      DeviceId            ;
    quint16     DataType            ;
    quint64     Time                ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ScanHeader
{
    quint16     ScanNumber          ;
    quint16     ScannerStatus       ;
    quint16     SyncPhaseOffset     ;
    quint64     ScanStartTime       ;
    quint64     ScanEndTime         ;
    quint16     AngleTicks          ;
    qint16      StartAngle          ;
    qint16      EndAngle            ;
    quint16     ScanPoints          ;
    qint16      MountingYawAngle    ;
    qint16      MountingPitchAngle  ;
    qint16      MountingRollAngle   ;
    qint16      MountingX           ;
    qint16      MountingY           ;
    qint16      MountingZ           ;
    quint16     Reserved            ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ScanPoint
{
    quint8      LayerEcho           ;
    quint8      Flags               ;
    qint16      HorizontalAngle     ;
    quint16     RadialDistance      ;
    quint16     EchoPulseWidth      ;
    quint16     Reserved            ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ErrorRegisters
{
    quint16     ErrorRegister1      ;
    quint16     ErrorRegister2      ;
    quint16     WarningRegister1    ;
    quint16     WarningRegister2    ;
    quint16     Reserved1           ;
    quint16     Reserved2           ;
    quint16     Reserved3           ;
    quint16     Reserved4           ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandCommon
{
    quint16     CommandId           ;
    quint16     Reserved            ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandSetParameter
{
    quint16     CommandId           ;
    quint16     Reserved            ;
    quint16     ParameterIndex      ;
    quint32     Parameter           ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandGetParameter
{
    quint16     CommandId           ;
    quint16     Reserved            ;
    quint16     ParameterIndex      ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandTime
{
    quint16     CommandId           ;
    quint32     Reserved            ;
    quint32     Time                ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ReplyGetParameter
{
    quint16     ReplyId             ;
    quint16     ParameterIndex      ;
    quint32     Parameter           ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ReplyStatus
{
    quint16     ReplyId             ;
    quint16     FirmwareVersion     ;
    quint16     FPGAVersion         ;
    quint16     ScannerStatus       ;
    quint32     Reserved1           ;
    quint16     Temperature         ;
    quint16     SerialNumber0       ;
    quint16     SerialNumber1       ;
    quint16     Reserved2           ;
    quint16     FPGATime[3]         ;
    quint16     DSPTime[3]          ;
};
#pragma pack(pop)


class Command
{
public:
    static QByteArray Reset();
    static QByteArray GetStatus();
    static QByteArray SaveConfig();
    static QByteArray ResetDefaults();
    static QByteArray StartMeasure();
    static QByteArray StopMeasure();
    static QByteArray SetAddress(const QString&);
    static QByteArray SetPort(quint32);
    static QByteArray SetMask(quint32);
    static QByteArray SetGateway(quint32);
};


class Sensor : public QObject
{
    Q_OBJECT

public:
    explicit Sensor();

public:
    bool Connect(const QString&, quint16);
    bool Send(const QByteArray&);
    bool Disconnect();
    bool Connected() const;

signals:
    void OnChart(const QByteArray&);
    void OnState(const QByteArray&);
    void OnError(const QByteArray&);
    void OnSocket(QAbstractSocket::SocketError);

private slots:
    void OnRead();

private:
    QTcpSocket mSocket;
};

#endif
