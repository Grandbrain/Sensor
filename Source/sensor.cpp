#include "sensor.h"

void Converter::Convert(DataHeader& dataHeader)
{
    dataHeader.MagicWord            = qbswap(dataHeader.MagicWord);
    dataHeader.PreviousSize         = qbswap(dataHeader.PreviousSize);
    dataHeader.Size                 = qbswap(dataHeader.Size);
    dataHeader.Reserved             = qbswap(dataHeader.Reserved);
    dataHeader.DeviceId             = qbswap(dataHeader.DeviceId);
    dataHeader.DataType             = qbswap(dataHeader.DataType);
    dataHeader.Time                 = qbswap(dataHeader.Time);
}

void Converter::Convert(ScanHeader& scanHeader)
{
    scanHeader.ScanNumber           = qbswap(scanHeader.ScanNumber);
    scanHeader.ScannerStatus        = qbswap(scanHeader.ScannerStatus);
    scanHeader.SyncPhaseOffset      = qbswap(scanHeader.SyncPhaseOffset);
    scanHeader.ScanStartTime        = qbswap(scanHeader.ScanStartTime);
    scanHeader.ScanEndTime          = qbswap(scanHeader.ScanEndTime);
    scanHeader.AngleTicks           = qbswap(scanHeader.AngleTicks);
    scanHeader.StartAngle           = qbswap(scanHeader.StartAngle);
    scanHeader.EndAngle             = qbswap(scanHeader.EndAngle);
    scanHeader.ScanPoints           = qbswap(scanHeader.ScanPoints);
    scanHeader.MountingYawAngle     = qbswap(scanHeader.MountingYawAngle);
    scanHeader.MountingPitchAngle   = qbswap(scanHeader.MountingPitchAngle);
    scanHeader.MountingRollAngle    = qbswap(scanHeader.MountingRollAngle);
    scanHeader.MountingX            = qbswap(scanHeader.MountingX);
    scanHeader.MountingY            = qbswap(scanHeader.MountingY);
    scanHeader.MountingZ            = qbswap(scanHeader.MountingZ);
    scanHeader.Reserved             = qbswap(scanHeader.Reserved);
}

void Converter::Convert(ScanPoint& scanPoint)
{
    scanPoint.LayerEcho             = qbswap(scanPoint.LayerEcho);
    scanPoint.Flags                 = qbswap(scanPoint.Flags);
    scanPoint.HorizontalAngle       = qbswap(scanPoint.HorizontalAngle);
    scanPoint.RadialDistance        = qbswap(scanPoint.RadialDistance);
    scanPoint.EchoPulseWidth        = qbswap(scanPoint.EchoPulseWidth);
    scanPoint.Reserved              = qbswap(scanPoint.Reserved);
}

void Converter::Convert(ObjectHeader& objectHeader)
{
    objectHeader.ScanStartTime      = qbswap(objectHeader.ScanStartTime);
    objectHeader.NumberOfObjects    = qbswap(objectHeader.NumberOfObjects);
}

void Converter::Convert(Point2& point)
{
    point.PositionX                 = qbswap(point.PositionX);
    point.PositionY                 = qbswap(point.PositionY);
}

void Converter::Convert(Size2& size)
{
    size.SizeX                      = qbswap(size.SizeX);
    size.SizeY                      = qbswap(size.SizeY);
}

void Converter::Convert(ObjectContent& content)
{
    content.ObjectId                = qbswap(content.ObjectId);
    content.ObjectAge               = qbswap(content.ObjectAge);
    content.ObjectPredictionAge     = qbswap(content.ObjectPredictionAge);
    content.RelativeTimestamp       = qbswap(content.RelativeTimestamp);
    content.ObjectBoxOrientation    = qbswap(content.ObjectBoxOrientation);
    content.Reserved1               = qbswap(content.Reserved1);
    content.Reserved2               = qbswap(content.Reserved2);
    content.Reserved3               = qbswap(content.Reserved3);
    content.NumberOfPoints          = qbswap(content.NumberOfPoints);
    Convert(content.ReferencePoint);
    Convert(content.ReferencePointSigma);
    Convert(content.ClosestPoint);
    Convert(content.BoundingBoxCenter);
    Convert(content.BoundingBoxSize);
    Convert(content.ObjectBoxCenter);
    Convert(content.ObjectBoxSize);
    Convert(content.AbsVelocity);
    Convert(content.AbsVelocitySigma);
    Convert(content.RelativeVelocity);
}

void Converter::Convert(ErrorRegisters& errorRegisters)
{
    errorRegisters.ErrorRegister1   = qbswap(errorRegisters.ErrorRegister1);
    errorRegisters.ErrorRegister2   = qbswap(errorRegisters.ErrorRegister2);
    errorRegisters.WarningRegister1 = qbswap(errorRegisters.WarningRegister1);
    errorRegisters.WarningRegister2 = qbswap(errorRegisters.WarningRegister2);
    errorRegisters.Reserved1        = qbswap(errorRegisters.Reserved1);
    errorRegisters.Reserved2        = qbswap(errorRegisters.Reserved2);
    errorRegisters.Reserved3        = qbswap(errorRegisters.Reserved3);
    errorRegisters.Reserved4        = qbswap(errorRegisters.Reserved4);
}

void Converter::Convert(CommandCommon& commandCommon)
{
    commandCommon.CommandId         = qbswap(commandCommon.CommandId);
    commandCommon.Reserved          = qbswap(commandCommon.Reserved);
}


void Converter::Convert(CommandSetParameter& setParameter)
{
    setParameter.CommandId          = qbswap(setParameter.CommandId);
    setParameter.Reserved           = qbswap(setParameter.Reserved);
    setParameter.ParameterIndex     = qbswap(setParameter.ParameterIndex);
    setParameter.Parameter          = qbswap(setParameter.Parameter);
}

void Converter::Convert(CommandGetParameter& getParameter)
{
    getParameter.CommandId          = qbswap(getParameter.CommandId);
    getParameter.Reserved           = qbswap(getParameter.Reserved);
    getParameter.ParameterIndex     = qbswap(getParameter.ParameterIndex);
}

void Converter::Convert(CommandTime& commandTime)
{
    commandTime.CommandId           = qbswap(commandTime.CommandId);
    commandTime.Reserved            = qbswap(commandTime.Reserved);
    commandTime.Time                = qbswap(commandTime.Time);
}

void Converter::Convert(ReplyGetParameter& getParameter)
{
    getParameter.ReplyId            = qbswap(getParameter.ReplyId);
    getParameter.ParameterIndex     = qbswap(getParameter.ParameterIndex);
    getParameter.Parameter          = qbswap(getParameter.Parameter);
}

void Converter::Convert(ReplyStatus& status)
{
    status.ReplyId                  = qbswap(status.ReplyId);
    status.FirmwareVersion          = qbswap(status.FirmwareVersion);
    status.FPGAVersion              = qbswap(status.FPGAVersion);
    status.ScannerStatus            = qbswap(status.ScannerStatus);
    status.Reserved1                = qbswap(status.Reserved1);
    status.Temperature              = qbswap(status.Temperature);
    status.SerialNumber0            = qbswap(status.SerialNumber0);
    status.SerialNumber1            = qbswap(status.SerialNumber1);
    status.Reserved2                = qbswap(status.Reserved2);
    status.FPGATime[0]              = qbswap(status.FPGATime[0]);
    status.FPGATime[1]              = qbswap(status.FPGATime[1]);
    status.FPGATime[2]              = qbswap(status.FPGATime[2]);
    status.DSPTime[0]               = qbswap(status.DSPTime[0]);
    status.DSPTime[1]               = qbswap(status.DSPTime[1]);
    status.DSPTime[2]               = qbswap(status.DSPTime[2]);
}




void Command::Reset(QByteArray& array)
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
    Converter::Convert(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Command::GetStatus(QByteArray& array)
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
    Converter::Convert(dataHeader);
    array.clear();
    array.append((char*)&dataHeader, sizeof dataHeader);
    array.append((char*)&commandCommon, sizeof commandCommon);
}

void Command::SaveConfig(QByteArray& array)
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
    Converter::Convert(dataHeader);
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
    QByteArray data = mSocket.readAll();
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
        int count = (size - sizeof(DataHeader) - sizeof(ScanHeader)) / sizeof(ScanPoint);

        scanData.scanHeader = scanHeader;
        for(int i = 0; i < count; i++)
        {
            int offset = sizeof(DataHeader) + sizeof(ScanHeader) + i * sizeof(ScanPoint);
            ScanPoint point = *reinterpret_cast<ScanPoint*>(offset);
            scanData.scanPoints.append(point);
        }
        emit Update(scanData);
        mData.clear();
    }
}
