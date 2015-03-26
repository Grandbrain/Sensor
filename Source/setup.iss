[Setup]
AllowNetworkDrive=no
AllowUNCPath=no
AlwaysShowComponentsList=yes
AppCopyright=Copyright (C) 2015 Andrey Lomakin
AppName=Sensor
AppPublisher=Andrey Lomakin
AppVerName=Sensor 1.0
AppVersion=1.0
ArchitecturesAllowed=x64 
ArchitecturesInstallIn64BitMode=x64
DefaultDirName={pf}\Sensor
DefaultGroupName=Sensor
LicenseFile=license.txt
OutputBaseFilename=setup
SignedUninstaller=yes
SignTool=signtool
SetupIconFile=icon.ico
UninstallDisplayIcon={app}\Sensor.exe,0
UninstallDisplayName=Sensor
VersionInfoVersion=1.0.0.0
WizardImageFile=large.bmp
WizardSmallImageFile=small.bmp 

[Files]
Source: "*.dll"; DestDir: "{app}"
Source: "Sensor.exe"; DestDir: "{app}"
Source: "settings.ini"; DestDir: "{app}"
Source: "vcredist_x64.exe"; DestDir: "{app}"; Flags: dontcopy
Source: "bearer\*"; DestDir: "{app}\bearer"
Source: "iconengines\*"; DestDir: "{app}\iconengines"
Source: "imageformats\*"; DestDir: "{app}\imageformats"
Source: "platforms\*"; DestDir: "{app}\platforms"

[CustomMessages]
en.InstallRedist=Installing Microsoft Visual C++ Redistributable 2013...
ru.InstallRedist=Установка Microsoft Visual C++ Redistributable 2013...

[Icons]
Name: "{group}\Sensor"; Filename: "{app}\Sensor.exe"; WorkingDir: "{app}"
Name: "{userdesktop}\Sensor"; Filename: "{app}\Sensor.exe"; WorkingDir: "{app}"

[Run]
Filename: "{app}\vcredist_x64.exe"; Parameters: "/install /quiet /norestart"; StatusMsg: "{cm:InstallRedist}"; Check: Check

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"
Name: "ru"; MessagesFile: "compiler:Languages\Russian.isl"
       
[Code]
function MsiQueryProductState(szProduct: String): Longint;
external 'MsiQueryProductStateW@msi.dll stdcall'; function Check(): Boolean;
begin Result := MsiQueryProductState('{A749D8E6-B613-3BE3-8F5F-045C84EBA29B}') <> 5; end;