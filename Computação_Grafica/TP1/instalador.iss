; Instalador do TP1 (Inno Setup 6.3 ou mais novo)
; Antes de compilar, rode o build.bat para gerar a pasta dist\TP1_CG

[Setup]
AppName=TP1 - Computação Gráfica
AppVersion=1.0
DefaultDirName={autopf}\TP1_CG
DefaultGroupName=TP1 - Computação Gráfica
UninstallDisplayIcon={app}\TP1_CG.exe
OutputDir=Output
OutputBaseFilename=Setup_TP1_CG
Compression=lzma2
SolidCompression=yes
WizardStyle=modern
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

[Languages]
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"

[Types]
Name: "completa"; Description: "Instalação completa"
Name: "personalizada"; Description: "Instalação personalizada"; Flags: iscustom

[Components]
Name: "programa"; Description: "Programa"; Types: completa personalizada; Flags: fixed
Name: "bibliotecas"; Description: "Bibliotecas e componentes de execução"; Types: completa personalizada; Flags: fixed
Name: "fonte"; Description: "Código-fonte"; Types: completa

[Tasks]
Name: "atalhodesktop"; Description: "Criar atalho na área de trabalho"; GroupDescription: "Atalhos:"; Flags: unchecked

[Files]
Source: "dist\TP1_CG\TP1_CG.exe"; DestDir: "{app}"; Components: programa; Flags: ignoreversion
Source: "dist\TP1_CG\_internal\*"; DestDir: "{app}\_internal"; Components: bibliotecas; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "main.py"; DestDir: "{app}\codigo-fonte"; Components: fonte; Flags: ignoreversion
Source: "area_desenho.py"; DestDir: "{app}\codigo-fonte"; Components: fonte; Flags: ignoreversion
Source: "rasterizacao.py"; DestDir: "{app}\codigo-fonte"; Components: fonte; Flags: ignoreversion
Source: "estruturas.py"; DestDir: "{app}\codigo-fonte"; Components: fonte; Flags: ignoreversion
Source: "recorte.py"; DestDir: "{app}\codigo-fonte"; Components: fonte; Flags: ignoreversion
Source: "transformacoes.py"; DestDir: "{app}\codigo-fonte"; Components: fonte; Flags: ignoreversion
Source: "preenchimento.py"; DestDir: "{app}\codigo-fonte"; Components: fonte; Flags: ignoreversion

[Icons]
Name: "{group}\TP1 - Computação Gráfica"; Filename: "{app}\TP1_CG.exe"
Name: "{group}\Desinstalar TP1 - Computação Gráfica"; Filename: "{uninstallexe}"
Name: "{autodesktop}\TP1 - Computação Gráfica"; Filename: "{app}\TP1_CG.exe"; Tasks: atalhodesktop
