#ifndef SENSOR_H
#define SENSOR_H

#include <QtNetwork>
#include <QString>

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
