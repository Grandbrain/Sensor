#ifndef SENSOR_H
#define SENSOR_H

#include <QtNetwork>
#include <QString>

enum class Parameter
{
    Address                 ,
    Port                    ,
    SubnetMask              ,
    Gateway                 ,
    DataOutputFlags         ,
    StartAngle              ,
    EndAngle                ,
    ScanFrequency           ,
    SyncAngleOffset         ,
    AngularResolution
};

enum class Command
{
    Reset                   ,
    GetStatus               ,
    SaveConfig              ,
    SetParameter            ,
    GetParameter            ,
    ResetParameters         ,
    StartMeasure            ,
    StopMeasure             ,
    SetTimeSeconds          ,
    SetTimeFractionalSeconds
};

struct Point
{
    bool                Transparent         ;
    bool                Clutter             ;
    bool                Dirt                ;
    quint8              Layer               ;
    quint8              Echo                ;
    qreal               HorizontalAngle     ;
    qreal               RadialDistance      ;
    quint16             EchoPulseWidth      ;
};

struct ScanData
{
    bool                FrequencyReached    ;
    bool                ExternalSyncSignal  ;
    bool                SyncOk              ;
    bool                SyncMaster          ;
    quint16             ScanNumber          ;
    quint16             SyncPhaseOffset     ;
    quint64             ScanStartTimeNTP    ;
    quint64             ScanEndTimeNTP      ;
    quint16             AngleTicks          ;
    qint16              StartAngle          ;
    qint16              EndAngle            ;
    quint16             PointsNumber        ;
    qint16              MountingYaw         ;
    qint16              MountingPitch       ;
    qint16              MountingRoll        ;
    qint16              MountingX           ;
    qint16              MountingY           ;
    qint16              MountingZ           ;
    QVector<Point>      Points              ;
};

struct ErrorsWarnings
{
    bool                E1CS                ;
    bool                E1SBTI              ;
    bool                E1SBO               ;
    bool                E1APDOT             ;
    bool                E1APDUT             ;
    bool                E2CS                ;
    bool                E2ICD               ;
    bool                E2CCIP              ;
    bool                E2DPT               ;
    bool                W1IT                ;
    bool                W1ET                ;
    bool                W1CSSF              ;
    bool                W2CS                ;
    bool                W2EIB               ;
    bool                W2CED               ;
    bool                W2FC                ;
    bool                W2MAF               ;
};

struct Status
{
    bool                PhaseLocked         ;
    bool                ExternalSyncSignal  ;
    bool                FrequencyLocked     ;
    bool                LaserOn             ;
    bool                MotorOn             ;
    QString             FirmwareVersion     ;
    QString             FPGAVersion         ;
    QString             SerialNumber        ;
    qreal               Temperature         ;
    QString             FPGATime            ;
    QString             DSPTime             ;
};

struct Parameters
{
    Parameter           ParameterChanged    ;
    QString             Address             ;
    QString             SubnetMask          ;
    QString             Gateway             ;
    QPair<bool, bool>   DataOutputFlags     ;
    quint16             Port                ;
    quint16             ScanFrequency       ;
    qint16              SyncAngleOffset     ;
    quint16             AngularResolution   ;
    qint16              StartAngle          ;
    qint16              EndAngle            ;
};

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit                Sensor                      (QObject* = 0);
    virtual                 ~Sensor                     () = default;

public:
    void                    Connect                     (const QString&, quint16);
    void                    Disconnect                  ();
    bool                    Connected                   () const;
    bool                    Reset                       ();
    bool                    GetStatus                   ();
    bool                    SaveConfig                  ();
    bool                    ResetParameters             ();
    bool                    StartMeasure                ();
    bool                    StopMeasure                 ();
    bool                    SetTimeSeconds              (quint32);
    bool                    SetTimeFractionalSeconds    (quint32);
    bool                    SetAddress                  (const QString&);
    bool                    SetPort                     (quint16);
    bool                    SetSubnetMask               (const QString&);
    bool                    SetGateway                  (const QString&);
    bool                    SetDataOutputFlags          (bool, bool);
    bool                    SetStartAngle               (qint16);
    bool                    SetEndAngle                 (qint16);
    bool                    SetScanFrequency            (quint16);
    bool                    SetSyncAngleOffset          (qint16);
    bool                    SetAngularResolutionType    (quint16);
    bool                    GetAddress                  ();
    bool                    GetPort                     ();
    bool                    GetSubnetMask               ();
    bool                    GetGateway                  ();
    bool                    GetDataOutputFlags          ();
    bool                    GetStartAngle               ();
    bool                    GetEndAngle                 ();
    bool                    GetScanFrequency            ();
    bool                    GetSyncAngleOffset          ();
    bool                    GetAngularResolutionType    ();
    QPair<qint16, qint16>   GetStartAngleBoundary       ();
    QPair<qint16, qint16>   GetEndAngleBoundary         ();
    QPair<qint16, qint16>   GetSyncAngleBoundary        ();
    QVector<quint16>        GetScanFrequencyValues      ();
    QVector<quint16>        GetAngularResolutionValues  ();
    quint16                 GetAngleTicksPerRotation    ();

private:
    bool                    Send                        (const QByteArray&);
    void                    Parse                       ();

signals:
    void                    OnPoints                    (const ScanData&);
    void                    OnWarnings                  (const ErrorsWarnings&);
    void                    OnParameters                (const Parameters&);
    void                    OnStatus                    (const Status&);
    void                    OnFailed                    (Command);
    void                    OnDisconnected              ();
    void                    OnConnected                 ();
    void                    OnError                     ();

private slots:
    void                    OnReadyRead                 ();

private:
    QTcpSocket              mSocket ;
    QByteArray              mArray  ;
};

#endif
