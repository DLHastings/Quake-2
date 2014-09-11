@ECHO OFF 
FOR %%f IN (*.dll) DO XCOPY C:\Users\dlh24_000\Documents\GitHub\Quake 2\release\"%%f" C:\Program Files (x86)\Steam\SteamApps\common\Quake 2\baseq2 /m /y
REM XCOPY c:\original c:\backupfolder /m /e /y