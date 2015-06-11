#include <type_traits>
#include "sensor.h"

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

struct ScanHeader
{
    quint16 ScanNumber;
    quint16 ScannerStatus;
    quint16 SyncPhaseOffset;
    quint64 ScanStartTime;
    quint64 ScanEndTime;
    quint16 AngleTicks;
    qint16 StartAngle;
    qint16 EndAngle;
    quint16 ScanPoints;
    qint16 MountingYawAngle;
    qint16 MountingPitchAngle;
    qint16 MountingRollAngle;
    qint16 MountingX;
    qint16 MountingY;
    qint16 MountingZ;
    quint16 Reserved;
};

struct ScanPoint
{
    quint8 LayerEcho;
    quint8 Flags;
    qint16 HorizontalAngle;
    quint16 RadialDistance;
    quint16 EchoPulseWidth;
    quint16 Reserved;
};

struct ObjectHeader
{
    quint64 ScanStartTime;
    quint16 NumberOfObjects;
};

struct Point2D
{
    qint16 PositionX;
    qint16 PositionY;
};

struct Size2D
{
    quint16 SizeX;
    quint16 SizeY;
};

struct ObjectData
{
    quint16 ObjectID;
    quint16 ObjectAge;
    quint16 ObjectPredictionAge;
    quint16 RelativeTime;
    Point2D ReferencePoint;
    Point2D ReferencePointSigma;
    Point2D ClosestPoint;
    Point2D BoundingBoxCenter;
    Size2D BoundingBoxSize;
    Point2D ObjectCenter;
    Size2D ObjectSize;
    qint16 ObjectOrientation;
    Point2D AbsoluteSpeed;
    Size2D AbsoluteSpeedSigma;
    Point2D RelativeSpeed;
    quint16 Reserved1;
    quint16 Reserved2;
    quint16 Reserved3;
    quint16 NumberContourPoints;
};

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

struct CommandCommon
{
    quint16 CommandId;
    quint16 Reserved;
};

struct CommandSetParameter
{
    quint16 CommandId;
    quint16 Reserved;
    quint16 ParameterIndex;
    quint32 Parameter;
};

struct CommandGetParameter
{
    quint16 CommandId;
    quint16 Reserved;
    quint16 ParameterIndex;
};

struct CommandTime
{
    quint16 CommandId;
    quint32 Reserved;
    quint32 Time;
};

struct Reply
{
    quint16 Id;
};

struct ReplyGetParameter
{
    quint16 ParameterIndex;
    quint32 Parameter;
};

struct ReplyStatus
{
    quint16 FirmwareVersion;
    quint16 FPGAVersion;
    quint16 ScannerStatus;
    quint32 Reserved1;
    quint16 Temperature;
    quint16 SerialNumber0;
    quint16 SerialNumber1;
    quint16 Reserved2;
    quint16 FPGATime1;
    quint16 FPGATime2;
    quint16 FPGATime3;
    quint16 DSPTime1;
    quint16 DSPTime2;
    quint16 DSPTime3;
};
#pragma pack(pop)


class Converter
{
    explicit Converter() = delete;
    virtual ~Converter() = delete;

    static void convert(DataHeader& dataHeader)
    {
        dataHeader.MagicWord = qbswap(dataHeader.MagicWord);
        dataHeader.PreviousSize = qbswap(dataHeader.PreviousSize);
        dataHeader.Size = qbswap(dataHeader.Size);
        dataHeader.Reserved = qbswap(dataHeader.Reserved);
        dataHeader.DeviceId = qbswap(dataHeader.DeviceId);
        dataHeader.DataType = qbswap(dataHeader.DataType);
        dataHeader.Time = qbswap(dataHeader.Time);
    }

    static void convert(ScanHeader& scanHeader)
    {
        scanHeader.ScanNumber = qbswap(scanHeader.ScanNumber);
        scanHeader.ScannerStatus = qbswap(scanHeader.ScannerStatus);
        scanHeader.SyncPhaseOffset = qbswap(scanHeader.SyncPhaseOffset);
        scanHeader.ScanStartTime = qbswap(scanHeader.ScanStartTime);
        scanHeader.ScanEndTime = qbswap(scanHeader.ScanEndTime);
        scanHeader.AngleTicks = qbswap(scanHeader.AngleTicks);
        scanHeader.StartAngle = qbswap(scanHeader.StartAngle);
        scanHeader.EndAngle = qbswap(scanHeader.EndAngle);
        scanHeader.ScanPoints = qbswap(scanHeader.ScanPoints);
        scanHeader.MountingYawAngle = qbswap(scanHeader.MountingYawAngle);
        scanHeader.MountingPitchAngle = qbswap(scanHeader.MountingPitchAngle);
        scanHeader.MountingRollAngle = qbswap(scanHeader.MountingRollAngle);
        scanHeader.MountingX = qbswap(scanHeader.MountingX);
        scanHeader.MountingY = qbswap(scanHeader.MountingY);
        scanHeader.MountingZ = qbswap(scanHeader.MountingZ);
        scanHeader.Reserved = qbswap(scanHeader.Reserved);
    }

    static void convert(ScanPoint& scanPoint)
    {
        scanPoint.LayerEcho = qbswap(scanPoint.LayerEcho);
        scanPoint.Flags = qbswap(scanPoint.Flags);
        scanPoint.HorizontalAngle = qbswap(scanPoint.HorizontalAngle);
        scanPoint.RadialDistance = qbswap(scanPoint.RadialDistance);
        scanPoint.EchoPulseWidth = qbswap(scanPoint.EchoPulseWidth);
        scanPoint.Reserved = qbswap(scanPoint.Reserved);
    }

    static void convert(ObjectHeader& objectHeader)
    {
        objectHeader.ScanStartTime = qbswap(objectHeader.ScanStartTime);
        objectHeader.NumberOfObjects = qbswap(objectHeader.NumberOfObjects);
    }

    static void convert(Point2D& point2d)
    {
        point2d.PositionX = qbswap(point2d.PositionX);
        point2d.PositionY = qbswap(point2d.PositionY);
    }

    static void convert(Size2D& size2d)
    {
        size2d.SizeX = qbswap(size2d.SizeX);
        size2d.SizeY = qbswap(size2d.SizeY);
    }

    static void convert(ObjectData& objectData)
    {
        objectData.ObjectID = qbswap(objectData.ObjectID);
        objectData.ObjectAge = qbswap(objectData.ObjectAge);
        objectData.ObjectPredictionAge = qbswap(objectData.ObjectPredictionAge);
        objectData.RelativeTime = qbswap(objectData.RelativeTime);
        objectData.ObjectOrientation = qbswap(objectData.ObjectOrientation);
        objectData.Reserved1 = qbswap(objectData.Reserved1);
        objectData.Reserved2 = qbswap(objectData.Reserved2);
        objectData.Reserved3 = qbswap(objectData.Reserved3);
        objectData.NumberContourPoints = qbswap(objectData.NumberContourPoints);
        convert(objectData.ReferencePoint);
        convert(objectData.ReferencePointSigma);
        convert(objectData.ClosestPoint);
        convert(objectData.BoundingBoxCenter);
        convert(objectData.BoundingBoxSize);
        convert(objectData.ObjectCenter);
        convert(objectData.ObjectSize);
        convert(objectData.AbsoluteSpeed);
        convert(objectData.AbsoluteSpeedSigma);
        convert(objectData.RelativeSpeed);
    }

    static void convert(ErrorRegisters& errorRegisters)
    {
        errorRegisters.ErrorRegister1 = qbswap(errorRegisters.ErrorRegister1);
        errorRegisters.ErrorRegister2 = qbswap(errorRegisters.ErrorRegister2);
        errorRegisters.WarningRegister1 = qbswap(errorRegisters.WarningRegister1);
        errorRegisters.WarningRegister2 = qbswap(errorRegisters.WarningRegister2);
        errorRegisters.Reserved1 = qbswap(errorRegisters.Reserved1);
        errorRegisters.Reserved2 = qbswap(errorRegisters.Reserved2);
        errorRegisters.Reserved3 = qbswap(errorRegisters.Reserved3);
        errorRegisters.Reserved4 = qbswap(errorRegisters.Reserved4);
    }

    static void convert(CommandCommon& commandCommon)
    {
        commandCommon.CommandId = qbswap(commandCommon.CommandId);
        commandCommon.Reserved = qbswap(commandCommon.Reserved);
    }

    static void convert(CommandSetParameter& commandSetParameter)
    {
        commandSetParameter.CommandId = qbswap(commandSetParameter.CommandId);
        commandSetParameter.Reserved = qbswap(commandSetParameter.Reserved);
        commandSetParameter.ParameterIndex = qbswap(commandSetParameter.ParameterIndex);
        commandSetParameter.Parameter = qbswap(commandSetParameter.Parameter);
    }

    static void convert(CommandGetParameter& commandGetParameter)
    {
        commandGetParameter.CommandId = qbswap(commandGetParameter.CommandId);
        commandGetParameter.Reserved = qbswap(commandGetParameter.Reserved);
        commandGetParameter.ParameterIndex = qbswap(commandGetParameter.ParameterIndex);
    }

    static void convert(CommandTime& commandTime)
    {
        commandTime.CommandId = qbswap(commandTime.CommandId);
        commandTime.Reserved = qbswap(commandTime.Reserved);
        commandTime.Time = qbswap(commandTime.Time);
    }

    static void convert(Reply& reply)
    {
        reply.Id = qbswap(reply.Id);
    }

    static void convert(ReplyGetParameter& replyGetParameter)
    {
        replyGetParameter.ParameterIndex = qbswap(replyGetParameter.ParameterIndex);
        replyGetParameter.Parameter = qbswap(replyGetParameter.Parameter);
    }

    static void convert(ReplyStatus& replyStatus)
    {
        replyStatus.FirmwareVersion = qbswap(replyStatus.FirmwareVersion);
        replyStatus.FPGAVersion = qbswap(replyStatus.FPGAVersion);
        replyStatus.ScannerStatus = qbswap(replyStatus.ScannerStatus);
        replyStatus.Reserved1 = qbswap(replyStatus.Reserved1);
        replyStatus.Temperature = qbswap(replyStatus.Temperature);
        replyStatus.SerialNumber0 = qbswap(replyStatus.SerialNumber0);
        replyStatus.SerialNumber1 = qbswap(replyStatus.SerialNumber1);
        replyStatus.Reserved2 = qbswap(replyStatus.Reserved2);
        replyStatus.FPGATime1 = qbswap(replyStatus.FPGATime1);
        replyStatus.FPGATime2 = qbswap(replyStatus.FPGATime2);
        replyStatus.FPGATime3 = qbswap(replyStatus.FPGATime3);
        replyStatus.DSPTime1 = qbswap(replyStatus.DSPTime1);
        replyStatus.DSPTime2 = qbswap(replyStatus.DSPTime2);
        replyStatus.DSPTime3 = qbswap(replyStatus.DSPTime3);
    }

public:

    template<typename T>
    static void Convert(T& t)
    {
        qint32 a = 0x1;
        qint8* b = (qint8*)&a;
        bool little = b[0] == 1;
        if(little && std::is_same<T, DataHeader>::value) convert(t);
        if(little && !std::is_same<T, DataHeader>::value) return;
        if(!little && !std::is_same<T, DataHeader>::value) convert(t);
        else return;
    }
};


class Utilites
{
    explicit Utilites() = delete;
    virtual ~Utilites() = delete;

public:

    template<typename A, typename B>
    static void ToArray(QByteArray& array, A& a, B& b)
    {
        Converter::Convert(a);
        Converter::Convert(b);
        array.append((char*)&a, sizeof a);
        array.append((char*)&b, sizeof b);
    }

    static QString ConvertTime(quint16 a, quint16 b, quint16 c)
    {
        QDate date(QString::number(a, 16).toInt(),
            QString::number(((b >> 8) & 0xff), 16).toInt(),
            QString::number((b & 0xff), 16).toInt());
        QTime time(QString::number(((c >> 8) & 0xff), 16).toInt(),
            QString::number((c & 0xff), 16).toInt());
        return QDateTime(date, time).toString("d.M.yyyy / H.m");
    }

    static QString ConvertVersion(quint16 v)
    {
        QString version = QString::number(v, 16);
        int count = 0;
        for(int i = version.length() - 1; i >= 0; --i)
        {
            if(version.at(i) == QChar('0')) ++count;
            else break;
        }
        QString result = version.at(0);
        for(int i = 1; i < version.length() - count; i++)
        {
            if(version.at(i).isDigit())
            {
                result.append('.');
                result.append(version.at(i));
            }
            else result.append(version.at(i));
        }
        return result;
    }

    static qreal ConvertTicks(qint16 angleTicks)
    {
        const qreal pi = 3.141592653589793238462;
        const qreal deg2rad = 0.01745329251994329576923690768;
        qreal angle = static_cast<qreal>(angleTicks) / 32.0 * deg2rad;
        if(angle > -1000.0 && angle < 1000.0)
        {
            while(angle > pi) angle -= 2.0 * pi;
            while(angle <= -pi) angle += 2.0 * pi;
        }
        else angle = 0.0;
        return angle;
    }

    static void CreateDataHeader(DataHeader& header, quint32 size, quint16 type)
    {
        header.MagicWord = 0xAFFEC0C2;
        header.PreviousSize = 0;
        header.Size = size;
        header.Reserved = 0;
        header.DeviceId = 0x07;
        header.DataType = type;
        header.Time = 0;
    }

    static void CreateCommandCommon(CommandCommon& command, quint16 id)
    {
        command.CommandId = id;
        command.Reserved = 0;
    }

    static void CreateSetParameter(CommandSetParameter& command, quint16 id, quint16 index, quint32 value)
    {
        command.CommandId = id;
        command.Reserved = 0;
        command.ParameterIndex = index;
        command.Parameter = value;
    }

    static void CreateGetParameter(CommandGetParameter& command, quint16 id, quint16 index)
    {
        command.CommandId = id;
        command.Reserved = 0;
        command.ParameterIndex = index;
    }

    static void CreateTime(CommandTime& time, quint16 id, quint32 value)
    {
        time.CommandId = id;
        time.Reserved = 0;
        time.Time = value;
    }

    static void Reset(QByteArray& array)
    {
        CommandCommon command;
        DataHeader header;
        CreateCommandCommon(command, 0x0000);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetStatus(QByteArray& array)
    {
        CommandCommon command;
        DataHeader header;
        CreateCommandCommon(command, 0x0001);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SaveConfig(QByteArray& array)
    {
        CommandCommon command;
        DataHeader header;
        CreateCommandCommon(command, 0x0004);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void ResetParameters(QByteArray& array)
    {
        CommandCommon command;
        DataHeader header;
        CreateCommandCommon(command, 0x001A);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void StartMeasure(QByteArray& array)
    {
        CommandCommon command;
        DataHeader header;
        CreateCommandCommon(command, 0x0020);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void StopMeasure(QByteArray& array)
    {
        CommandCommon command;
        DataHeader header;
        CreateCommandCommon(command, 0x0021);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void TimeSeconds(QByteArray& array, quint32 time)
    {
        CommandTime command;
        DataHeader header;
        CreateTime(command, 0x0030, time);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void TimeFractionalSeconds(QByteArray& array, quint32 time)
    {
        CommandTime command;
        DataHeader header;
        CreateTime(command, 0x0031, time);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetAddress(QByteArray& array, const QString& address)
    {
        QHostAddress a(address);
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1000, a.toIPv4Address());
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetPort(QByteArray& array, quint16 port)
    {
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1001, port);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetSubnetMask(QByteArray& array, const QString& mask)
    {
        QHostAddress a(mask);
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1002, a.toIPv4Address());
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetStandardGateway(QByteArray& array, const QString& gateway)
    {
        QHostAddress a(gateway);
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1003, a.toIPv4Address());
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetDataOutputFlags(QByteArray& array, bool enableScanData, bool enableErrors)
    {
        quint32 flags = 0;
        if(!enableScanData) flags |= 1 << 0;
        if(!enableErrors)   flags |= 1 << 4;
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1012, flags);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetStartAngle(QByteArray& array, qint16 angle)
    {
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1100, angle);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetEndAngle(QByteArray& array, qint16 angle)
    {
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1101, angle);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetScanFrequency(QByteArray& array, quint16 frequency)
    {
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1102, frequency);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetSyncAngleOffset(QByteArray& array, qint16 offset)
    {
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1103, offset);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void SetAngularResolutionType(QByteArray& array, quint16 type)
    {
        CommandSetParameter command;
        DataHeader header;
        CreateSetParameter(command, 0x0010, 0x1104, type);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetAddress(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1000);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetPort(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1001);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetSubnetMask(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1002);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetStandardGateway(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1003);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetDataOutputFlags(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1012);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetStartAngle(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1100);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetEndAngle(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1101);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetScanFrequency(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0010, 0x1102);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetSyncAngleOffset(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1103);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetAngularResolutionType(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1104);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }

    static void GetAngleTicksPerRotation(QByteArray& array)
    {
        CommandGetParameter command;
        DataHeader header;
        CreateGetParameter(command, 0x0011, 0x1105);
        CreateDataHeader(header, sizeof(command), 0x2010);
        ToArray(array, header, command);
    }
};

Sensor::Sensor()
{
    connect(&mSocket, SIGNAL(readyRead()), SLOT(OnReadyRead()));
    connect(&mSocket, SIGNAL(connected()), SIGNAL(OnConnected()));
    connect(&mSocket, SIGNAL(disconnected()), SIGNAL(OnDisconnected()));
    connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)), SIGNAL(OnError()));
}

Sensor::~Sensor()
{

}

void Sensor::Connect(const QString& address, quint16 port)
{
    mSocket.connectToHost(address, port);
}

void Sensor::Disconnect()
{
    mSocket.abort();
}

void Sensor::Reset()
{
    QByteArray array;
    Utilites::Reset(array);
    Push(array);
}

void Sensor::GetStatus()
{
    QByteArray array;
    Utilites::GetStatus(array);
    Push(array);
}

void Sensor::SaveConfig()
{
    QByteArray array;
    Utilites::SaveConfig(array);
    Push(array);
}

void Sensor::ResetParameters()
{
    QByteArray array;
    Utilites::ResetParameters(array);
    Push(array);
}

void Sensor::StartMeasure()
{
    QByteArray array;
    Utilites::StartMeasure(array);
    Push(array);
}

void Sensor::StopMeasure()
{
    QByteArray array;
    Utilites::StopMeasure(array);
    Push(array);
}

void Sensor::SetTimeSeconds(quint32 time)
{
    QByteArray array;
    Utilites::TimeSeconds(array, time);
    Push(array);
}

void Sensor::SetTimeFractionalSeconds(quint32 time)
{
    QByteArray array;
    Utilites::TimeFractionalSeconds(array, time);
    Push(array);
}

void Sensor::SetAddress(const QString& address)
{
    QByteArray array;
    Utilites::SetAddress(array, address);
    Push(array);
}

void Sensor::SetPort(quint16 port)
{
    QByteArray array;
    Utilites::SetPort(array, port);
    Push(array);
}

void Sensor::SetSubnetMask(const QString& mask)
{
    QByteArray array;
    Utilites::SetSubnetMask(array, mask);
    Push(array);
}

void Sensor::SetGateway(const QString& gateway)
{
    QByteArray array;
    Utilites::SetStandardGateway(array, gateway);
    Push(array);
}

void Sensor::SetDataOutputFlags(bool scan, bool errors)
{
    QByteArray array;
    Utilites::SetDataOutputFlags(array, scan, errors);
    Push(array);
}

void Sensor::SetStartAngle(qint16 angle)
{
    QByteArray array;
    Utilites::SetStartAngle(array, angle);
    Push(array);
}

void Sensor::SetEndAngle(qint16 angle)
{
    QByteArray array;
    Utilites::SetEndAngle(array, angle);
    Push(array);
}

void Sensor::SetScanFrequency(quint16 frequency)
{
    QByteArray array;
    Utilites::SetScanFrequency(array, frequency);
    Push(array);
}

void Sensor::SetSyncAngleOffset(qint16 offset)
{
    QByteArray array;
    Utilites::SetSyncAngleOffset(array, offset);
    Push(array);
}

void Sensor::SetAngularResolutionType(quint16 type)
{
    QByteArray array;
    Utilites::SetAngularResolutionType(array, type);
    Push(array);
}

void Sensor::GetAddress()
{
    QByteArray array;
    Utilites::GetAddress(array);
    Push(array);
}

void Sensor::GetPort()
{
    QByteArray array;
    Utilites::GetPort(array);
    Push(array);
}

void Sensor::GetSubnetMask()
{
    QByteArray array;
    Utilites::GetSubnetMask(array);
    Push(array);
}

void Sensor::GetGateway()
{
    QByteArray array;
    Utilites::GetStandardGateway(array);
    Push(array);
}

void Sensor::GetDataOutputFlags()
{
    QByteArray array;
    Utilites::GetDataOutputFlags(array);
    Push(array);
}

void Sensor::GetStartAngle()
{
    QByteArray array;
    Utilites::GetStartAngle(array);
    Push(array);
}

void Sensor::GetEndAngle()
{
    QByteArray array;
    Utilites::GetEndAngle(array);
    Push(array);
}

void Sensor::GetScanFrequency()
{
    QByteArray array;
    Utilites::GetScanFrequency(array);
    Push(array);
}

void Sensor::GetSyncAngleOffset()
{
    QByteArray array;
    Utilites::GetSyncAngleOffset(array);
    Push(array);
}

void Sensor::GetAngularResolutionType()
{
    QByteArray array;
    Utilites::GetAngularResolutionType(array);
    Push(array);
}

void Sensor::GetAngleTicksPerRotation()
{
    QByteArray array;
    Utilites::GetAngleTicksPerRotation(array);
    Push(array);
}

QPair<qint16, qint16> Sensor::GetStartAngleBoundary()
{
    return qMakePair(-1919, 1600);
}

QPair<qint16, qint16> Sensor::GetEndAngleBoundary()
{
    return qMakePair(-1920, 1599);
}

QPair<qint16, qint16> Sensor::GetSyncAngleBoundary()
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

QVector<quint16> Sensor::GetAngularResolutionValues()
{
    QVector<quint16> vector;
    vector.append(0);
    vector.append(1);
    vector.append(2);
    return vector;
}

void Sensor::Push(const QByteArray& array)
{
    mMutex.lock();
    mQueue.push_back(array);
    mMutex.unlock();
    QtConcurrent::run(this, &Sensor::Work);
}

void Sensor::Work()
{
    forever
    {
        QMutexLocker locker(&mMutex);
        if(mQueue.isEmpty()) break;
        QByteArray array = mQueue.front();
        mQueue.pop_front();
        locker.unlock();
        QMetaObject::invokeMethod(this, "OnWriting", Q_ARG(QByteArray, array));
    }
}

void Sensor::Parse()
{
    if(mArray.size() < sizeof(DataHeader)) return;
    DataHeader header = *reinterpret_cast<DataHeader*>(mArray.data());
    Converter::Convert(header);
    if(header.MagicWord != 0xAFFEC0C2) return;

    if(header.DataType == 0x2202)
    {
        if(mArray.size() < sizeof(DataHeader) + sizeof(ScanHeader)) return;
        ScanHeader scanHeader = *reinterpret_cast<ScanHeader*>(mArray.data() + sizeof(DataHeader));
        if(mArray.size() != sizeof(DataHeader) + sizeof(ScanHeader) +
                scanHeader.ScanPoints * sizeof(ScanPoint)) return;
        Converter::Convert(scanHeader);
        ScanData scanData;
        scanData.AngleTicks = scanHeader.AngleTicks;
        scanData.EndAngle = scanHeader.EndAngle;
        scanData.MountingPitch = scanHeader.MountingPitchAngle;
        scanData.MountingRoll = scanHeader.MountingRollAngle;
        scanData.MountingYaw = scanHeader.MountingYawAngle;
        scanData.MountingX = scanHeader.MountingX;
        scanData.MountingY = scanHeader.MountingY;
        scanData.MountingZ = scanHeader.MountingZ;
        scanData.PointsNumber = scanHeader.ScanPoints;
        scanData.ScanEndTimeNTP = scanHeader.ScanEndTime;
        scanData.ScanNumber = scanHeader.ScanNumber;
        scanData.ScanStartTimeNTP = scanHeader.ScanStartTime;
        scanData.StartAngle = scanHeader.StartAngle;
        scanData.SyncPhaseOffset = scanHeader.SyncPhaseOffset;
        scanData.ExternalSyncSignal = (scanHeader.ScannerStatus & 0x0010) != 0;
        scanData.FrequencyReached = (scanHeader.ScannerStatus & 0x0008) != 0;
        scanData.SyncMaster = (scanHeader.ScannerStatus & 0x0040) != 0;
        scanData.SyncOk = (scanHeader.ScannerStatus & 0x0020) != 0;
        for(quint16 i = 0; i < scanHeader.ScanPoints; i++)
        {
            ScanPoint scanPoint = *reinterpret_cast<ScanPoint*>(mArray.data() +
                sizeof(DataHeader) + sizeof(ScanHeader) + sizeof(ScanPoint) * i);
            Converter::Convert(scanPoint);
            Point point;
            point.Transparent = (scanPoint.Flags & 0x01) != 0;
            point.Clutter = (scanPoint.Flags & 0x02) != 0;
            point.Dirt = (scanPoint.Flags & 0x08) != 0;
            point.Layer = scanPoint.LayerEcho & 0x0F;
            point.Echo = (scanPoint.LayerEcho >> 4) & 0x0F;
            point.HorizontalAngle = Utilites::ConvertTicks(scanPoint.HorizontalAngle);
            point.RadialDistance = static_cast<qreal>(scanPoint.RadialDistance);
            point.EchoPulseWidth = scanPoint.EchoPulseWidth;
            scanData.Points.append(point);
        }
        emit OnPoints(scanData);
    }
    else if(header.DataType == 0x2030)
    {
        if(mArray.size() != sizeof(DataHeader) + sizeof(ErrorRegisters)) return;
        ErrorRegisters regs = *reinterpret_cast<ErrorRegisters*>(mArray.data() +
            sizeof(DataHeader));
        Converter::Convert(regs);
        ErrorsWarnings err;
        err.E1CS = (regs.ErrorRegister1 & 0x3C1F) != 0 || (regs.ErrorRegister1 & 0x300) == 0x300;
        err.E1SBTI = (regs.ErrorRegister1 & 0x04) != 0;
        err.E1SBO = (regs.ErrorRegister1 & 0x08) != 0;
        err.E1APDOT = (regs.ErrorRegister1 & 0x200) != 0;
        err.E1APDUT = (regs.ErrorRegister1 & 0x100) != 0;
        err.E2CS = (regs.ErrorRegister2 & 0x8F) != 0;
        err.E2ICD = (regs.ErrorRegister2 & 0x010) != 0;
        err.E2CCIP = (regs.ErrorRegister2 & 0x020) != 0;
        err.E2DPT = (regs.ErrorRegister1 & 0x040) != 0;
        err.W1IT = (regs.WarningRegister1 & 0x08) != 0;
        err.W1ET = (regs.WarningRegister1 & 0x010) != 0;
        err.W1CSSF = (regs.WarningRegister1 & 0x080) != 0;
        err.W2CS = (regs.WarningRegister2 & 0x048) != 0;
        err.W2EIB = (regs.WarningRegister2 & 0x02) != 0;
        err.W2CED = (regs.WarningRegister2 & 0x010) != 0;
        err.W2FC = (regs.WarningRegister2 & 0x020) != 0;
        err.W2MAF = (regs.WarningRegister2 & 0x040) != 0;
        emit OnWarnings(err);
    }
    else if(header.DataType == 0x2020)
    {
        if(mArray.size() < sizeof(DataHeader) + sizeof(quint16)) return;
        Reply replyId = *reinterpret_cast<Reply*>(mArray.data() + sizeof(DataHeader));
        Converter::Convert(replyId);
        if(replyId.Id & 0x8000)
        {
            replyId.Id &= ~(1 << 15);
            if(replyId.Id == 0x0000) emit OnFailed(Command::Reset);
            if(replyId.Id == 0x0001) emit OnFailed(Command::GetStatus);
            if(replyId.Id == 0x0004) emit OnFailed(Command::SaveConfig);
            if(replyId.Id == 0x0010) emit OnFailed(Command::SetParameter);
            if(replyId.Id == 0x0011) emit OnFailed(Command::GetParameter);
            if(replyId.Id == 0x001A) emit OnFailed(Command::ResetParameters);
            if(replyId.Id == 0x0020) emit OnFailed(Command::StartMeasure);
            if(replyId.Id == 0x0021) emit OnFailed(Command::StopMeasure);
            if(replyId.Id == 0x0030) emit OnFailed(Command::SetTimeSeconds);
            if(replyId.Id == 0x0031) emit OnFailed(Command::SetTimeFractionalSeconds);
        }
        if(replyId.Id == 0x0001)
        {
            if(mArray.size() != sizeof(DataHeader) + sizeof(quint16) + sizeof(ReplyStatus)) return;
            ReplyStatus param = *reinterpret_cast<ReplyStatus*>(mArray.data() +
                sizeof(DataHeader) + sizeof(quint16));
            Converter::Convert(param);
            Status p;
            p.MotorOn = (param.ScannerStatus & 0x01) != 0;
            p.LaserOn = (param.ScannerStatus & 0x02) != 0;
            p.FrequencyLocked = (param.ScannerStatus & 0x08) != 0;
            p.ExternalSyncSignal = (param.ScannerStatus & 0x10) != 0;
            p.PhaseLocked = (param.ScannerStatus & 0x20) != 0;
            p.Temperature = -(qreal(param.Temperature) - 579.2364) / 3.63;
            p.DSPTime = Utilites::ConvertTime(param.DSPTime1, param.DSPTime2, param.DSPTime3);
            p.FPGATime = Utilites::ConvertTime(param.FPGATime1, param.FPGATime2, param.FPGATime3);
            p.FirmwareVersion = Utilites::ConvertVersion(param.FirmwareVersion);
            p.FPGAVersion = Utilites::ConvertVersion(param.FPGAVersion);
            p.SerialNumber = QString::number((param.SerialNumber0 >> 8) & 0xff, 16) + '/' +
                    QString::number(param.SerialNumber0 & 0xff, 16) + ' '
                    + QString::number(param.SerialNumber1);
            emit OnStatus(p);
        }
        if(replyId.Id == 0x0011)
        {
            if(mArray.size() != sizeof(DataHeader) + sizeof(quint16) + sizeof(ReplyGetParameter))
                return;
            ReplyGetParameter param = *reinterpret_cast<ReplyGetParameter*>(mArray.data()
                + sizeof(DataHeader) + sizeof(quint16));
            Converter::Convert(param);
            Parameters p;
            if(param.ParameterIndex == 0x1000)
            {
                QHostAddress a(param.Parameter);
                p.Address = a.toString();
                p.ParameterChanged = Parameter::Address;
            }
            if(param.ParameterIndex == 0x1001)
            {
                p.Port = static_cast<quint16>(param.Parameter);
                p.ParameterChanged = Parameter::Port;
            }
            if(param.ParameterIndex == 0x1002)
            {
                QHostAddress a(param.Parameter);
                p.SubnetMask = a.toString();
                p.ParameterChanged = Parameter::SubnetMask;
            }
            if(param.ParameterIndex == 0x1003)
            {
                QHostAddress a(param.Parameter);
                p.Gateway = a.toString();
                p.ParameterChanged = Parameter::Gateway;
            }
            if(param.ParameterIndex == 0x1100)
            {
                p.StartAngle = param.Parameter;
                p.ParameterChanged = Parameter::StartAngle;
            }
            if(param.ParameterIndex == 0x1101)
            {
                p.EndAngle = param.Parameter;
                p.ParameterChanged = Parameter::EndAngle;
            }
            if(param.ParameterIndex == 0x1102)
            {
                p.ScanFrequency = param.Parameter;
                p.ParameterChanged = Parameter::ScanFrequency;
            }
            if(param.ParameterIndex == 0x1103)
            {
                p.SyncAngleOffset = param.Parameter;
                p.ParameterChanged = Parameter::SyncAngleOffset;
            }
            if(param.ParameterIndex == 0x1104)
            {
                p.AngularResolution = param.Parameter;
                p.ParameterChanged = Parameter::AngularResolution;
            }
            if(param.ParameterIndex == 0x1012)
            {
                p.DataOutputFlags.first = (param.Parameter & 0x01) != 0;
                p.DataOutputFlags.second = (param.Parameter & 0x10) != 0;
                p.ParameterChanged = Parameter::DataOutputFlags;
            }
            emit OnParameters(p);
        }
    }
}

void Sensor::OnWriting(const QByteArray& array)
{
    mSocket.write(array);
}

void Sensor::OnReadyRead()
{
    QByteArray array = mSocket.readAll();
    if(array.size() < sizeof(quint32)) return;
    DataHeader header;
    header.MagicWord = *reinterpret_cast<quint32*>(array.data());
    Converter::Convert(header);
    Parse();
    if(header.MagicWord == 0xAFFEC0C2) mArray.clear();
    mArray.append(array);
}
