; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=F800GS CB GUI Settings
AppVersion=0.2
DefaultDirName={autopf}\CBGUISettings
DefaultGroupName=CB GUI Settings
UninstallDisplayIcon={app}\CBGUISettings.exe
OutputBaseFilename=CBGUISettings_Installer
OutputDir=D:\Documents\git\cummutationBordGUISettings\Releases\v0.2
Compression=lzma2
SolidCompression=yes
WizardStyle=modern
SetupIconFile="D:\Documents\git\CBGUISettings\goose.ico"

[Types]
Name: "full"; Description: "Полная установка"
Name: "compact"; Description: "Обычная установка"
Name: "custom"; Description: "Выборочная установка"; Flags: iscustom

[Components]
Name: "desktopicon"; Description: "Создать ярлык на рабочем столе"; Types: full compact custom

[Files]
Source: "D:\Documents\git\cummutationBordGUISettings\build\Desktop_Qt_6_7_0_MinGW_64_bit-Release\release\cummutationBordGUISettings.exe"; \
    DestDir: "{app}"; DestName: "CBGUISettings.exe"; Flags: ignoreversion
Source: "D:\Documents\git\cummutationBordGUISettings\build\Desktop_Qt_6_7_0_MinGW_64_bit-Release\release\*.dll"; \
    DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "D:\Documents\git\CBGUISettings\goose.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\CB GUI Settings"; Filename: "{app}\CBGUISettings.exe"; IconFilename: "{app}\goose.ico"
Name: "{userdesktop}\CB GUI Settings"; Filename: "{app}\CBGUISettings.exe"; IconFilename: "{app}\goose.ico"; \
    Check: IsComponentSelected('desktopicon')


