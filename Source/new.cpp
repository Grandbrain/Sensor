#include <QtNetwork>
#include <type_traits>

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


class Const
{
    explicit Const() = delete;
    virtual ~Const() = delete;

public:

    static const qreal Pi = 3.141592653589793238462;
    static const qreal Deg2Rad = 0;
    static const QString Date = "";
};


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
    static void Push(QByteArray& array, A& a, B& b)
    {
        array.clear();
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
        return QDateTime(date, time).toString("hh:mm/dd.MM.yyyy");
    }
};
