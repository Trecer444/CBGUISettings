; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!
[Setup]
AppName=F800GS CB GUI Settings
AppVersion=0.3
DefaultDirName={autopf}\CBGUISettings
DefaultGroupName=CB GUI Settings
UninstallDisplayIcon={app}\CBGUISettings.exe
UninstallDisplayName=F800GS CB GUI Settings
OutputBaseFilename=CBGUISettings_Installer
OutputDir=D:\Documents\git\CBGUISettings\Releases\v0.2
Compression=lzma2
SolidCompression=yes
WizardStyle=modern
SetupIconFile="D:\Documents\git\CBGUISettings\goose.ico"
CreateAppDir=yes
DisableDirPage=no
DisableProgramGroupPage=no
LanguageDetectionMethod=none

[Languages]
Name: "ru"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "Создать ярлык на рабочем столе"

[Files]
Source: "D:\Documents\git\cummutationBordGUISettings\build\Desktop_Qt_6_7_0_MinGW_64_bit-Release\release\cummutationBordGUISettings.exe"; \
    DestDir: "{app}"; DestName: "CBGUISettings.exe"; Flags: ignoreversion
Source: "D:\Documents\git\cummutationBordGUISettings\build\Desktop_Qt_6_7_0_MinGW_64_bit-Release\release\*.dll"; \
    DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "D:\Documents\git\CBGUISettings\goose.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\CB GUI Settings"; Filename: "{app}\CBGUISettings.exe"; IconFilename: "{app}\goose.ico"
Name: "{userdesktop}\CB GUI Settings"; Filename: "{app}\CBGUISettings.exe"; IconFilename: "{app}\goose.ico"; \
    Tasks: desktopicon
    
[Run]
Filename: "{app}\CBGUISettings.exe"; Description: "Запустить F800GS CB GUI Settings"; Flags: nowait postinstall skipifsilent
