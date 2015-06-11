#ifndef SENSOR_H
#define SENSOR_H

#include <QtConcurrent/QtConcurrent>
#include <QtNetwork>
#include <QString>
#include <QMutex>

enum class Parameter
{
    Address,
    Port,
    SubnetMask,
    Gateway,
    DataOutputFlags,
    StartAngle,
    EndAngle,
    ScanFrequency,
    SyncAngleOffset,
    AngularResolution,
    AngleTicksPerRotation
};

enum class Command
{
    Reset,
    GetStatus,
    SaveConfig,
    SetParameter,
    GetParameter,
    ResetParameters,
    StartMeasure,
    StopMeasure,
    SetTimeSeconds,
    SetTimeFractionalSeconds
};

struct Point
{
    bool Transparent;
    bool Clutter;
    bool Dirt;
    quint8 Layer;
    quint8 Echo;
    qreal HorizontalAngle;
    qreal RadialDistance;
    quint16 EchoPulseWidth;
};

struct ScanData
{
    bool FrequencyReached;
    bool ExternalSyncSignal;
    bool SyncOk;
    bool SyncMaster;
    quint16 ScanNumber;
    quint16 SyncPhaseOffset;
    quint64 ScanStartTimeNTP;
    quint64 ScanEndTimeNTP;
    quint16 AngleTicks;
    qint16 StartAngle;
    qint16 EndAngle;
    quint16 PointsNumber;
    qint16 MountingYaw;
    qint16 MountingPitch;
    qint16 MountingRoll;
    qint16 MountingX;
    qint16 MountingY;
    qint16 MountingZ;
    QVector<Point> Points;
};

struct ErrorsWarnings
{
    bool E1CS;
    bool E1SBTI;
    bool E1SBO;
    bool E1APDOT;
    bool E1APDUT;
    bool E2CS;
    bool E2ICD;
    bool E2CCIP;
    bool E2DPT;
    bool W1IT;
    bool W1ET;
    bool W1CSSF;
    bool W2CS;
    bool W2EIB;
    bool W2CED;
    bool W2FC;
    bool W2MAF;
};

struct Status
{
    bool PhaseLocked;
    bool ExternalSyncSignal;
    bool FrequencyLocked;
    bool LaserOn;
    bool MotorOn;
    QString FirmwareVersion;
    QString FPGAVersion;
    QString SerialNumber;
    qreal Temperature;
    QString FPGATime;
    QString DSPTime;
};

struct Parameters
{
    Parameter ParameterChanged;
    QString Address;
    QString SubnetMask;
    QString Gateway;
    quint16 Port;
    quint16 ScanFrequency;
    qint16 SyncAngleOffset;
    quint16 AngularResolution;
    qint16 StartAngle;
    qint16 EndAngle;
    quint16 AngleTicksPerRotation;
    QPair<bool, bool> DataOutputFlags;
};

class Sensor : public QObject
{
    Q_OBJECT

public:
    Sensor();
   ~Sensor();

public:
    void Connect(const QString&, quint16);
    void Disconnect();
    void Reset();
    void GetStatus();
    void SaveConfig();
    void ResetParameters();
    void StartMeasure();
    void StopMeasure();
    void SetTimeSeconds(quint32);
    void SetTimeFractionalSeconds(quint32);
    void SetAddress(const QString&);
    void SetPort(quint16);
    void SetSubnetMask(const QString&);
    void SetGateway(const QString&);
    void SetDataOutputFlags(bool, bool);
    void SetStartAngle(qint16);
    void SetEndAngle(qint16);
    void SetScanFrequency(quint16);
    void SetSyncAngleOffset(qint16);
    void SetAngularResolutionType(quint16);
    void GetAddress();
    void GetPort();
    void GetSubnetMask();
    void GetGateway();
    void GetDataOutputFlags();
    void GetStartAngle();
    void GetEndAngle();
    void GetScanFrequency();
    void GetSyncAngleOffset();
    void GetAngularResolutionType();
    void GetAngleTicksPerRotation();
    QPair<qint16, qint16> GetStartAngleBoundary();
    QPair<qint16, qint16> GetEndAngleBoundary();
    QPair<qint16, qint16> GetSyncAngleBoundary();
    QVector<quint16> GetScanFrequencyValues();
    QVector<quint16> GetAngularResolutionValues();

private:
    void Push(const QByteArray&);
    void Parse();
    void Work();

signals:
    void OnPoints(const ScanData&);
    void OnWarnings(const ErrorsWarnings&);
    void OnParameters(const Parameters&);
    void OnStatus(const Status&);
    void OnFailed(Command);
    void OnDisconnected();
    void OnConnected();
    void OnError();

private slots:
    void OnReadyRead();
    void OnWriting(const QByteArray&);

private:
    QQueue<QByteArray> mQueue;
    QByteArray mArray;
    QTcpSocket mSocket;
    QMutex mMutex;
};

#endif

