#include "sensor.h"

void Utilites::SwapBytes(DataHeader& dataHeader)
{
    dataHeader.MagicWord    = qbswap(dataHeader.MagicWord);
    dataHeader.PreviousSize = qbswap(dataHeader.PreviousSize);
    dataHeader.Size         = qbswap(dataHeader.Size);
    dataHeader.Reserved     = qbswap(dataHeader.Reserved);
    dataHeader.DeviceId     = qbswap(dataHeader.DeviceId);
    dataHeader.DataType     = qbswap(dataHeader.DataType);
    dataHeader.Time         = qbswap(dataHeader.Time);
}

void Utilites::Reset(QByteArray& array)
{
    DataHeader dataHeader;
    dataHeader.MagicWord    = 0xAFFEC0C2;
    dataHeader.PreviousSize = 0;
    dataHeader.Size         = sizeof(CommandCommon);
    dataHeader.Reserved     = 0;
    dataHeader.DeviceId     = 0x07;
    dataHeader.DataType     = 0x2010;
    dataHeader.Time         = 0;
    CommandCommon commandCommon;
    commandCommon.CommandId = 0x0000;
    commandCommon.Reserved  = 0;
    SwapBytes(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Utilites::GetStatus(QByteArray& array)
{
    DataHeader dataHeader;
    dataHeader.MagicWord    = 0xAFFEC0C2;
    dataHeader.PreviousSize = 0;
    dataHeader.Size         = sizeof(CommandCommon);
    dataHeader.Reserved     = 0;
    dataHeader.DeviceId     = 0;
    dataHeader.DataType     = 0x2010;
    dataHeader.Time         = 0;
    CommandCommon commandCommon;
    commandCommon.CommandId = 0x0001;
    commandCommon.Reserved  = 0;
    SwapBytes(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Utilites::SaveConfig(QByteArray& array)
{
    DataHeader dataHeader;
    dataHeader.MagicWord    = 0xAFFEC0C2;
    dataHeader.PreviousSize = 0;
    dataHeader.Size         = sizeof(CommandCommon);
    dataHeader.Reserved     = 0;
    dataHeader.DeviceId     = 0x07;
    dataHeader.DataType     = 0x2010;
    dataHeader.Time         = 0;
    CommandCommon commandCommon;
    commandCommon.CommandId = 0x0004;
    commandCommon.Reserved  = 0;
    SwapBytes(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Command::ResetDefaults(QByteArray& array)
{
    DataHeader dataHeader;
    dataHeader.MagicWord    = 0xAFFEC0C2;
    dataHeader.PreviousSize = 0;
    dataHeader.Size         = sizeof(CommandCommon);
    dataHeader.Reserved     = 0;
    dataHeader.DeviceId     = 0x07;
    dataHeader.DataType     = 0x2010;
    dataHeader.Time         = 0;
    CommandCommon commandCommon;
    commandCommon.CommandId = 0x001A;
    commandCommon.Reserved  = 0;
    Converter::Convert(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Command::StartMeasure(QByteArray& array)
{
    DataHeader dataHeader;
    dataHeader.MagicWord    = 0xAFFEC0C2;
    dataHeader.PreviousSize = 0;
    dataHeader.Size         = sizeof(CommandCommon);
    dataHeader.Reserved     = 0;
    dataHeader.DeviceId     = 0x07;
    dataHeader.DataType     = 0x2010;
    dataHeader.Time         = 0;
    CommandCommon commandCommon;
    commandCommon.CommandId = 0x0020;
    commandCommon.Reserved  = 0;
    Converter::Convert(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Command::StopMeasure(QByteArray& array)
{
    DataHeader dataHeader;
    dataHeader.MagicWord    = 0xAFFEC0C2;
    dataHeader.PreviousSize = 0;
    dataHeader.Size         = sizeof(CommandCommon);
    dataHeader.Reserved     = 0;
    dataHeader.DeviceId     = 0x07;
    dataHeader.DataType     = 0x2010;
    dataHeader.Time         = 0;
    CommandCommon commandCommon;
    commandCommon.CommandId = 0x0021;
    commandCommon.Reserved  = 0;
    Converter::Convert(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Command::SetAddress(QByteArray& array, const QString& address)
{
    QHostAddress addr(address);
    DataHeader dataHeader;
    dataHeader.MagicWord    = 0xAFFEC0C2;
    dataHeader.PreviousSize = 0;
    dataHeader.Size         = sizeof(CommandSetParameter);
    dataHeader.Reserved     = 0;
    dataHeader.DeviceId     = 0x07;
    dataHeader.DataType     = 0x2010;
    dataHeader.Time         = 0;
    CommandSetParameter parameter;
    parameter.CommandId     = 0x0010;
    parameter.Reserved      = 0;
    parameter.ParameterIndex= 0x1000;
    parameter.Parameter     = addr.toIPv4Address();
    Converter::Convert(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&parameter, sizeof parameter);
}




Sensor::Sensor()
{
    connect(&mSocket, SIGNAL(readyRead()), SLOT(OnRead()));
    connect(&mSocket, SIGNAL(connected()), SLOT(OnConnect()));
    connect(&mSocket, SIGNAL(disconnected()), SLOT(OnDisconnect()));
    connect(&mSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(OnState(QAbstractSocket::SocketState)));
    connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(OnError(QAbstractSocket::SocketError)));
}

bool Sensor::Connect(const QString& address, quint16 port)
{
    mSocket.connectToHost(address, port);
    return mSocket.waitForConnected();
}

bool Sensor::Disconnect()
{
    mSocket.disconnectFromHost();
    return mSocket.waitForDisconnected();
}

bool Sensor::Connected() const
{
    QAbstractSocket::SocketState state = mSocket.state();
    return state == QAbstractSocket::ConnectedState;
}

bool Sensor::Send(const QByteArray& array)
{
    if(!Connected()) return false;
    qint64 size = mSocket.write(array);
    bool written = mSocket.waitForBytesWritten();
    if (size != array.size() || !written) return false;
    return true;
}

void Sensor::OnState(QAbstractSocket::SocketState)
{

}

void Sensor::OnError(QAbstractSocket::SocketError)
{
}

void Sensor::OnDisconnect()
{

}

void Sensor::OnConnect()
{
}

void Sensor::OnRead()
{
    /*QByteArray data = mSocket.readAll();
    if((uint)data.size() < sizeof(DataHeader)) return;

    DataHeader header = *reinterpret_cast<DataHeader*>(data.data());
    Converter::Convert(header);
    if(header.MagicWord == 0xAFFEC0C2)
    {
        ScanHeader scanHeader = *reinterpret_cast<ScanHeader*>(data.data() + sizeof(DataHeader));
        int count = (data.size() - sizeof(DataHeader) - sizeof(ScanHeader)) / sizeof(ScanPoint);
        if(count < scanHeader.ScanPoints) remainPoints = scanHeader.ScanPoints - count;
        mData.append(data);
    }
    else if(remainPoints != 0)
    {
        mData.append(data);
        remainPoints -= (data.size() / sizeof(ScanPoint));
    }
    else
    {
        ScanData scanData;
        ScanHeader scanHeader = *reinterpret_cast<ScanHeader*>(mData.data() + sizeof(DataHeader));
        int count = (data.size() - sizeof(DataHeader) - sizeof(ScanHeader)) / sizeof(ScanPoint);

        scanData.scanHeader = scanHeader;
        for(int i = 0; i < count; i++)
        {
            int offset = sizeof(DataHeader) + sizeof(ScanHeader) + i * sizeof(ScanPoint);
            ScanPoint point = *reinterpret_cast<ScanPoint*>(offset);
            scanData.scanPoints.append(point);
        }
        emit Update(scanData);
        mData.clear();
    }*/
}
