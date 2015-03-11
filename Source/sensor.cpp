#include "sensor.h"

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
struct ObjectHeader
{
    quint64     ScanStartTime       ;
    quint16     NumberOfObjects     ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct Point2D
{
    qint16      PositionX           ;
    qint16      PositionY           ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct Size2D
{
    quint16      SizeX              ;
    quint16      SizeY              ;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ObjectData
{
    quint16     ObjectID            ;
    quint16     ObjectAge           ;
    quint16     ObjectPredictionAge ;
    quint16     RelativeTime        ;
    Point2D     ReferencePoint      ;
    Point2D     ReferencePointSigma ;
    Point2D     ClosestPoint        ;
    Point2D     BoundingBoxCenter   ;
    Size2D      BoundingBoxSize     ;
    Point2D     ObjectCenter        ;
    Size2D      ObjectSize          ;
    qint16      ObjectOrientation   ;
    Point2D     AbsoluteSpeed       ;
    Size2D      AbsoluteSpeedSigma  ;
    Point2D     RelativeSpeed       ;
    quint16     Reserved1           ;
    quint16     Reserved2           ;
    quint16     Reserved3           ;
    quint16     NumberContourPoints ;
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


class Utils
{
public:

    explicit Utils() = delete;
    virtual ~Utils() = delete;

public:

    template<typename A, typename B> static QByteArray Push(A& a, B& b)
    {
        QByteArray array;
        Swap(a);
        array.append((char*)&a, sizeof a);
        array.append((char*)&b, sizeof b);
        return array;
    }

    static void Delay(ulong ms)
    {
        class Thread : QThread
        {public: static void Delay(ulong ms) {msleep(ms);}};
        Thread::Delay(ms);
    }

    static void Swap(DataHeader& header)
    {
        header.MagicWord        = qbswap(header.MagicWord);
        header.PreviousSize     = qbswap(header.PreviousSize);
        header.Size             = qbswap(header.Size);
        header.Reserved         = qbswap(header.Reserved);
        header.DeviceId         = qbswap(header.DeviceId);
        header.DataType         = qbswap(header.DataType);
        header.Time             = qbswap(header.Time);
    }

    static DataHeader CreateDataHeader(quint32 size, quint16 type)
    {
        DataHeader header;
        header.MagicWord        = 0xAFFEC0C2;
        header.PreviousSize     = 0;
        header.Size             = size;
        header.Reserved         = 0;
        header.DeviceId         = 0x07;
        header.DataType         = type;
        header.Time             = 0;
        return header;
    }

    static CommandCommon CreateCommandCommon(quint16 id)
    {
        CommandCommon command;
        command.CommandId       = id;
        command.Reserved        = 0;
        return command;
    }

    static CommandSetParameter CreateSetParameter(quint16 id, quint16 index, quint32 value)
    {
        CommandSetParameter command;
        command.CommandId       = id;
        command.Reserved        = 0;
        command.ParameterIndex  = index;
        command.Parameter       = value;
        return command;
    }

    static CommandGetParameter CreateGetParameter(quint16 id, quint16 index)
    {
        CommandGetParameter command;
        command.CommandId       = id;
        command.Reserved        = 0;
        command.ParameterIndex  = index;
        return command;
    }

    static CommandTime CreateTime(quint16 id, quint32 value)
    {
        CommandTime time;
        time.CommandId          = id;
        time.Reserved           = 0;
        time.Time               = value;
        return time;
    }

    static QByteArray Reset()
    {
        CommandCommon command = CreateCommandCommon(0x0000);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetStatus()
    {
        CommandCommon command = CreateCommandCommon(0x0001);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SaveConfig()
    {
        CommandCommon command = CreateCommandCommon(0x0004);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray ResetDefaults()
    {
        CommandCommon command = CreateCommandCommon(0x001A);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray StartMeasure()
    {
        CommandCommon command = CreateCommandCommon(0x0020);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray StopMeasure()
    {
        CommandCommon command = CreateCommandCommon(0x0021);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray TimeSeconds(quint32 time)
    {
        CommandTime command = CreateTime(0x0030, time);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray TimeFractionalSeconds(quint32 time)
    {
        CommandTime command = CreateTime(0x0031, time);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetAddress(const QString& address)
    {
        QHostAddress a(address);
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1000, a.toIPv4Address());
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetPort(quint16 port)
    {
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1001, port);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetSubnetMask(const QString& mask)
    {
        QHostAddress m(mask);
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1002, m.toIPv4Address());
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetStandardGateway(const QString& gateway)
    {
        QHostAddress g(gateway);
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1003, g.toIPv4Address());
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetDataOutputFlags(bool enableScanData, bool enableErrors)
    {
        quint32 flags = 0;
        if(!enableScanData) flags |= 1 << 0;
        if(!enableErrors)   flags |= 1 << 4;
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1012, flags);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetStartAngle(qint16 angle)
    {
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1100, angle);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetEndAngle(qint16 angle)
    {
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1101, angle);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetScanFrequency(quint16 frequency)
    {
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1102, frequency);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetSyncAngleOffset(qint16 offset)
    {
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1103, offset);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray SetAngularResolutionType(quint16 type)
    {
        CommandSetParameter command = CreateSetParameter(0x0010, 0x1104, type);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetAddress()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1000);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetPort()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1001);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetSubnetMask()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1002);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetStandardGateway()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1003);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetDataOutputFlags()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1012);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetStartAngle()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1100);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetEndAngle()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1101);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetScanFrequency()
    {
        CommandGetParameter command = CreateGetParameter(0x0010, 0x1102);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetSyncAngleOffset()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1103);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetAngularResolutionType()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1104);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }

    static QByteArray GetAngleTicksPerRotation()
    {
        CommandGetParameter command = CreateGetParameter(0x0011, 0x1105);
        DataHeader header = CreateDataHeader(sizeof command, 0x2010);
        return Push(header, command);
    }
};


Sensor::Sensor()
{
    mDelay = 0;
    mPoints.second = false;
    mParams.second = false;
    mErrors.second = false;
    mStatus.second = false;
    connect(&mSocket, SIGNAL(readyRead()), SLOT(OnReadyRead()));
    connect(&mSocket, SIGNAL(connected()), SIGNAL(OnConnected()));
    connect(&mSocket, SIGNAL(disconnected()), SIGNAL(OnDisconnected()));
    connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)), SIGNAL(OnError()));
}

void Sensor::Connect(const QString& address, quint16 port)
{
    mSocket.connectToHost(address, port);
}

void Sensor::Disconnect()
{
    mSocket.disconnectFromHost();
}

bool Sensor::Connected() const
{
    return mSocket.state() == QAbstractSocket::ConnectedState;
}

bool Sensor::Reset()
{
    return Send(Utils::Reset());
}

bool Sensor::GetStatus()
{
    return Send(Utils::GetStatus());
}

bool Sensor::SaveConfig()
{
    return Send(Utils::SaveConfig());
}

bool Sensor::ResetDefaults()
{
    return Send(Utils::ResetDefaults());
}

bool Sensor::StartMeasure()
{
    return Send(Utils::StartMeasure());
}

bool Sensor::StopMeasure()
{
    return Send(Utils::StopMeasure());
}

bool Sensor::SetTimeSeconds(quint32 time)
{
    return Send(Utils::TimeSeconds(time));
}

bool Sensor::SetTimeFractionalSeconds(quint32 time)
{
    return Send(Utils::TimeFractionalSeconds(time));
}

bool Sensor::SetAddress(const QString& address)
{
    return Send(Utils::SetAddress(address));
}

bool Sensor::SetPort(quint16 port)
{
    return Send(Utils::SetPort(port));
}

bool Sensor::SetSubnetMask(const QString& mask)
{
    return Send(Utils::SetSubnetMask(mask));
}

bool Sensor::SetGateway(const QString& gateway)
{
    return Send(Utils::SetStandardGateway(gateway));
}

bool Sensor::SetDataOutputFlags(bool scan, bool errors)
{
    return Send(Utils::SetDataOutputFlags(scan, errors));
}

bool Sensor::SetStartAngle(qint16 angle)
{
    return Send(Utils::SetStartAngle(angle));
}

bool Sensor::SetEndAngle(qint16 angle)
{
    return Send(Utils::SetEndAngle(angle));
}

bool Sensor::SetScanFrequency(quint16 frequency)
{
    return Send(Utils::SetScanFrequency(frequency));
}

bool Sensor::SetSyncAngleOffset(qint16 offset)
{
    return Send(Utils::SetSyncAngleOffset(offset));
}

bool Sensor::SetAngularResolutionType(quint16 type)
{
    return Send(Utils::SetAngularResolutionType(type));
}

bool Sensor::GetAddress()
{
    return Send(Utils::GetAddress());
}

bool Sensor::GetPort()
{
    return Send(Utils::GetPort());
}

bool Sensor::GetSubnetMask()
{
    return Send(Utils::GetSubnetMask());
}

bool Sensor::GetGateway()
{
    return Send(Utils::GetStandardGateway());
}

bool Sensor::GetDataOutputFlags()
{
    return Send(Utils::GetDataOutputFlags());
}

bool Sensor::GetStartAngle()
{
    return Send(Utils::GetStartAngle());
}

bool Sensor::GetEndAngle()
{
    return Send(Utils::GetEndAngle());
}

bool Sensor::GetScanFrequency()
{
    return Send(Utils::GetScanFrequency());
}

bool Sensor::GetSyncAngleOffset()
{
    return Send(Utils::GetSyncAngleOffset());
}

bool Sensor::GetAngularResolutionType()
{
    return Send(Utils::GetAngularResolutionType());
}

bool Sensor::GetAngleTicksPerRotation()
{
    return Send(Utils::GetAngleTicksPerRotation());
}

QPair<qint16, qint16> Sensor::GetStartAngleBoundaryValues()
{
    return qMakePair(-1919, 1600);
}

QPair<qint16, qint16> Sensor::GetEndAngleBoundaryValues()
{
    return qMakePair(-1920, 1599);
}

QPair<qint16, qint16> Sensor::GetSyncAngleBoundaryValues()
{
    return qMakePair(-5760, 5759);
}

QVector<quint16> Sensor::GetScanFrequencyValues()
{
    QVector<quint16> vector;
    vector.append(3200);
    vector.append(6400);
    vector.append(12800);
    return vector;
}

QVector<quint16> Sensor::GetAngularResolutionTypeValues()
{
    QVector<quint16> vector;
    vector.append(0);
    vector.append(1);
    vector.append(2);
    return vector;
}

void Sensor::SetCommandDelay(ulong delay)
{
    mDelay = delay;
}

bool Sensor::Send(const QByteArray& array)
{
    if(mDelay) Utils::Delay(mDelay);
    return mSocket.write(array) == array.size();
}

void Sensor::OnReadyRead()
{
    QByteArray array = mSocket.readAll();
    if(array.isEmpty()) return;


}
