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


class Command
{
public:
    static QByteArray Reset();
    static QByteArray GetStatus();
    static QByteArray SaveConfig();
    static QByteArray ResetDefaults();
    static QByteArray StartMeasure();
    static QByteArray StopMeasure();
    static QByteArray SetAddress(const QString&);
    static QByteArray SetPort(quint32);
    static QByteArray SetMask(quint32);
    static QByteArray SetGateway(quint32);
};






void Swap(DataHeader& header)
{
    header.MagicWord    = qbswap(header.MagicWord);
    header.PreviousSize = qbswap(header.PreviousSize);
    header.Size         = qbswap(header.Size);
    header.Reserved     = qbswap(header.Reserved);
    header.DeviceId     = qbswap(header.DeviceId);
    header.DataType     = qbswap(header.DataType);
    header.Time         = qbswap(header.Time);
}

DataHeader Create(quint32 size, quint16 type)
{
    DataHeader header;
    header.MagicWord    = 0xAFFEC0C2;
    header.PreviousSize = 0;
    header.Size         = size;
    header.Reserved     = 0;
    header.DeviceId     = 0x07;
    header.DataType     = type;
    header.Time         = 0;
    return header;
}

CommandCommon Create(quint16 id)
{
    CommandCommon command;
    command.CommandId   = id;
    command.Reserved    = 0;
    return command;
}

CommandSetParameter Create(quint16 id, quint16 index, quint32 value)
{
    CommandSetParameter command;
    command.CommandId       = id;
    command.Reserved        = 0;
    command.ParameterIndex  = index;
    command.Parameter       = value;
    return command;
}

template<class A, class B> QByteArray Push(A& a, B& b)
{
    QByteArray array;
    Swap(a);
    array.clear();
    array.append((char*)&a, sizeof a);
    array.append((char*)&b, sizeof b);
    return array;
}

QByteArray Command::Reset()
{
    CommandCommon command = Create(0x0000);
    DataHeader header = Create(sizeof command, 0x2010);
    return Push(header, command);
}

QByteArray Command::GetStatus()
{
    CommandCommon command = Create(0x0001);
    DataHeader header = Create(sizeof command, 0x2010);
    return Push(header, command);
}

QByteArray Command::SaveConfig()
{
    CommandCommon command = Create(0x0004);
    DataHeader header = Create(sizeof command, 0x2010);
    return Push(header, command);
}

QByteArray Command::ResetDefaults()
{
    CommandCommon command = Create(0x001A);
    DataHeader header = Create(sizeof command, 0x2010);
    return Push(header, command);
}

QByteArray Command::StartMeasure()
{
    CommandCommon command = Create(0x0020);
    DataHeader header = Create(sizeof command, 0x2010);
    return Push(header, command);
}

QByteArray Command::StopMeasure()
{
    CommandCommon command = Create(0x0021);
    DataHeader header = Create(sizeof command, 0x2010);
    return Push(header, command);
}

QByteArray Command::SetAddress(const QString& address)
{
    QHostAddress addr(address);
    CommandSetParameter command = Create(0x0010, 0x1000, addr.toIPv4Address());
    DataHeader header = Create(sizeof command, 0x2010);
    return Push(header, command);
}

Sensor::Sensor()
{
    connect(&mSocket, SIGNAL(readyRead()), SLOT(OnRead()));
    connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)), SIGNAL(OnSocket(QAbstractSocket::SocketError)));
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

void Sensor::OnRead()
{
    QByteArray data = mSocket.readAll();

    DataHeader header = *reinterpret_cast<DataHeader*>(data.data());
    Swap(header);
    //if(header.MagicWord == 0xAFFEC0C2)

    /*if(header.MagicWord == 0xAFFEC0C2)
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
