#include "sensor.h"

void Converter::Convert(DataHeader& dataHeader)
{
    dataHeader.MagicWord                = qbswap(dataHeader.MagicWord);
    dataHeader.PreviousSize             = qbswap(dataHeader.PreviousSize);
    dataHeader.Size                     = qbswap(dataHeader.Size);
    dataHeader.Reserved                 = qbswap(dataHeader.Reserved);
    dataHeader.DeviceId                 = qbswap(dataHeader.DeviceId);
    dataHeader.DataType                 = qbswap(dataHeader.DataType);
    dataHeader.Time                     = qbswap(dataHeader.Time);
}

void Converter::Convert(ScanHeader& scanHeader)
{
    scanHeader.ScanNumber               = qbswap(scanHeader.ScanNumber);
    scanHeader.ScannerStatus            = qbswap(scanHeader.ScannerStatus);
    scanHeader.SyncPhaseOffset          = qbswap(scanHeader.SyncPhaseOffset);
    scanHeader.ScanStartTime            = qbswap(scanHeader.ScanStartTime);
    scanHeader.ScanEndTime              = qbswap(scanHeader.ScanEndTime);
    scanHeader.AngleTicksPerRotation    = qbswap(scanHeader.AngleTicksPerRotation);
    scanHeader.StartAngle               = qbswap(scanHeader.StartAngle);
    scanHeader.EndAngle                 = qbswap(scanHeader.EndAngle);
    scanHeader.ScanPoints               = qbswap(scanHeader.ScanPoints);
    scanHeader.Reserved1                = qbswap(scanHeader.Reserved1);
    scanHeader.Reserved2                = qbswap(scanHeader.Reserved2);
    scanHeader.Reserved3                = qbswap(scanHeader.Reserved3);
    scanHeader.Reserved4                = qbswap(scanHeader.Reserved4);
    scanHeader.Reserved5                = qbswap(scanHeader.Reserved5);
    scanHeader.Reserved6                = qbswap(scanHeader.Reserved6);
    scanHeader.Reserved7                = qbswap(scanHeader.Reserved7);
}

void Converter::Convert(ScanPoint& scanPoint)
{
    scanPoint.LayerEcho                 = qbswap(scanPoint.LayerEcho);
    scanPoint.Flags                     = qbswap(scanPoint.Flags);
    scanPoint.HorizontalAngle           = qbswap(scanPoint.HorizontalAngle);
    scanPoint.RadialDistance            = qbswap(scanPoint.RadialDistance);
    scanPoint.EchoPulseWidth            = qbswap(scanPoint.EchoPulseWidth);
    scanPoint.Reserved                  = qbswap(scanPoint.Reserved);
}

void Converter::Convert(ErrorRegisters& errorRegisters)
{
    errorRegisters.ErrorRegister1       = qbswap(errorRegisters.ErrorRegister1);
    errorRegisters.ErrorRegister2       = qbswap(errorRegisters.ErrorRegister2);
    errorRegisters.WarningRegister1     = qbswap(errorRegisters.WarningRegister1);
    errorRegisters.WarningRegister2     = qbswap(errorRegisters.WarningRegister2);
    errorRegisters.Reserved1            = qbswap(errorRegisters.Reserved1);
    errorRegisters.Reserved2            = qbswap(errorRegisters.Reserved2);
    errorRegisters.Reserved3            = qbswap(errorRegisters.Reserved3);
    errorRegisters.Reserved4            = qbswap(errorRegisters.Reserved4);
}

void Converter::Convert(CommandCommon& commandCommon)
{
    commandCommon.CommandId             = qbswap(commandCommon.CommandId);
    commandCommon.Reserved              = qbswap(commandCommon.Reserved);
}


void Converter::Convert(CommandSetParameter& setParameter)
{
    setParameter.CommandId              = qbswap(setParameter.CommandId);
    setParameter.Reserved               = qbswap(setParameter.Reserved);
    setParameter.ParameterIndex         = qbswap(setParameter.ParameterIndex);
    setParameter.Parameter              = qbswap(setParameter.Parameter);
}

void Converter::Convert(CommandGetParameter& getParameter)
{
    getParameter.CommandId              = qbswap(getParameter.CommandId);
    getParameter.Reserved               = qbswap(getParameter.Reserved);
    getParameter.ParameterIndex         = qbswap(getParameter.ParameterIndex);
}

void Converter::Convert(CommandTime& commandTime)
{
    commandTime.CommandId               = qbswap(commandTime.CommandId);
    commandTime.Reserved                = qbswap(commandTime.Reserved);
    commandTime.Time                    = qbswap(commandTime.Time);
}

void Converter::Convert(ReplyGetParameter& getParameter)
{
    getParameter.ReplyId                = qbswap(getParameter.ReplyId);
    getParameter.ParameterIndex         = qbswap(getParameter.ParameterIndex);
    getParameter.Parameter              = qbswap(getParameter.Parameter);
}

void Converter::Convert(ReplyStatus& status)
{
    status.ReplyId                      = qbswap(status.ReplyId);
    status.FirmwareVersion              = qbswap(status.FirmwareVersion);
    status.FPGAVersion                  = qbswap(status.FPGAVersion);
    status.ScannerStatus                = qbswap(status.ScannerStatus);
    status.Reserved1                    = qbswap(status.Reserved1);
    status.Temperature                  = qbswap(status.Temperature);
    status.SerialNumber0                = qbswap(status.SerialNumber0);
    status.SerialNumber1                = qbswap(status.SerialNumber1);
    status.Reserved2                    = qbswap(status.Reserved2);
    status.FPGATime[0]                  = qbswap(status.FPGATime[0]);
    status.FPGATime[1]                  = qbswap(status.FPGATime[1]);
    status.FPGATime[2]                  = qbswap(status.FPGATime[2]);
    status.DSPTime[0]                   = qbswap(status.DSPTime[0]);
    status.DSPTime[1]                   = qbswap(status.DSPTime[1]);
    status.DSPTime[2]                   = qbswap(status.DSPTime[2]);
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
    dataHeader.DeviceId     = 0x07;
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
