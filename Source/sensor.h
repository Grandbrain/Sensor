#ifndef SENSOR_H
#define SENSOR_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QtEndian>
#include <QtGlobal>
#include <QString>

#pragma pack(push, 1)
struct DataHeader
{
    quint32 MagicWord;
    quint32 PreviousSize;
    quint32 Size;
    quint8 Reserved;
    quint8 DeviceId;
    quint16 DataType;
    quint64 Time;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ScanHeader
{
    quint16 ScanNumber;
    quint16 ScannerStatus;
    quint16 SyncPhaseOffset;
    quint64 ScanStartTime;
    quint64 ScanEndTime;
    quint16 AngleTicksPerRotation;
    qint16 StartAngle;
    qint16 EndAngle;
    quint16 ScanPoints;
    qint16 Reserved1;
    qint16 Reserved2;
    qint16 Reserved3;
    qint16 Reserved4;
    qint16 Reserved5;
    qint16 Reserved6;
    quint16 Reserved7;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ScanPoint
{
    quint8 LayerEcho;
    quint8 Flags;
    qint16 HorizontalAngle;
    quint16 RadialDistance;
    quint16 EchoPulseWidth;
    quint16 Reserved;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ErrorRegisters
{
    quint16 ErrorRegister1;
    quint16 ErrorRegister2;
    quint16 WarningRegister1;
    quint16 WarningRegister2;
    quint16 Reserved1;
    quint16 Reserved2;
    quint16 Reserved3;
    quint16 Reserved4;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandCommon
{
    quint16 CommandId;
    quint16 Reserved;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandSetParameter
{
    quint16 CommandId;
    quint16 Reserved;
    quint16 ParameterIndex;
    quint32 Parameter;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandGetParameter
{
    quint16 CommandId;
    quint16 Reserved;
    quint16 ParameterIndex;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct CommandTime
{
    quint16 CommandId;
    quint32 Reserved;
    quint32 Time;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ReplyGetParameter
{
    quint16 ReplyId;
    quint16 ParameterIndex;
    quint32 Parameter;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ReplyStatus
{
    quint16 ReplyId;
    quint16 FirmwareVersion;
    quint16 FPGAVersion;
    quint16 ScannerStatus;
    quint32 Reserved1;
    quint16 Temperature;
    quint16 SerialNumber0;
    quint16 SerialNumber1;
    quint16 Reserved2;
    quint16 FPGATime[3];
    quint16 DSPTime[3];
};
#pragma pack(pop)


class Converter
{
public:
    Converter() = delete;
    static void Convert(DataHeader&);
    static void Convert(ScanHeader&);
    static void Convert(ScanPoint&);
    static void Convert(ErrorRegisters&);
    static void Convert(CommandCommon&);
    static void Convert(CommandSetParameter&);
    static void Convert(CommandGetParameter&);
    static void Convert(CommandTime&);
    static void Convert(ReplyGetParameter&);
    static void Convert(ReplyStatus&);
};


class Command
{
public:
    Command() = delete;
    static void Reset(QByteArray&);
    static void GetStatus(QByteArray&);
    static void SaveConfig(QByteArray&);
    static void ResetDefaults(QByteArray&);
    static void StartMeasure(QByteArray&);
    static void StopMeasure(QByteArray&);
    static void SetAddress(QByteArray&, const QString&);
    static void SetPort(QByteArray&, quint32);
    static void SetMask(QByteArray&, quint32);
    static void SetGateway(QByteArray&, quint32);
};


class QTcpClient : public QObject
{
    Q_OBJECT
public:
    QTcpClient(QObject*);
    bool Connect(const QString&, quint32);
    bool Connected() const;
private slots:
private:
    QTcpSocket mSocket;
};

#endif
