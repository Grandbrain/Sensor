#ifndef SENSOR_H
#define SENSOR_H

#include <QtNetwork>
#include <QString>

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor();
    virtual ~Sensor() = default;

public:
    void SetCommandDelay(ulong);
    void Connect(const QString&, quint16);
    void Disconnect();
    bool Connected() const;
    bool Reset();
    bool GetStatus();
    bool SaveConfig();
    bool ResetDefaults();
    bool StartMeasure();
    bool StopMeasure();
    bool SetTimeSeconds(quint32);
    bool SetTimeFractionalSeconds(quint32);
    bool SetAddress(const QString&);
    bool SetPort(quint16);
    bool SetSubnetMask(const QString&);
    bool SetGateway(const QString&);
    bool SetDataOutputFlags(bool, bool);
    bool SetStartAngle(qint16);
    bool SetEndAngle(qint16);
    bool SetScanFrequency(quint16);
    bool SetSyncAngleOffset(qint16);
    bool SetAngularResolutionType(quint16);
    bool GetAddress();
    bool GetPort();
    bool GetSubnetMask();
    bool GetGateway();
    bool GetDataOutputFlags();
    bool GetStartAngle();
    bool GetEndAngle();
    bool GetScanFrequency();
    bool GetSyncAngleOffset();
    bool GetAngularResolutionType();
    bool GetAngleTicksPerRotation();
    QPair<qint16, qint16> GetStartAngleBoundaryValues();
    QPair<qint16, qint16> GetEndAngleBoundaryValues();
    QPair<qint16, qint16> GetSyncAngleBoundaryValues();
    QVector<quint16> GetScanFrequencyValues();
    QVector<quint16> GetAngularResolutionTypeValues();

private:
    bool Send(const QByteArray&);

signals:
    void OnPoints();
    void OnWarnings();
    void OnParameters();
    void OnStatus();
    void OnDisconnected();
    void OnConnected();
    void OnError();

private slots:
    void OnReadyRead();

private:
    ulong mDelay;
    QTcpSocket mSocket;
    QPair<QByteArray, bool> mPoints;
    QPair<QByteArray, bool> mStatus;
    QPair<QByteArray, bool> mErrors;
    QPair<QByteArray, bool> mParams;
};

#endif
