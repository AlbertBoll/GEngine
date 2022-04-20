import subprocess, sys
import globals

ret = 0

if globals.IsWindows():
    ret = subprocess.call(["cmd.exe", "/c", "vendor\\bin\\premake\\premake5", "vs2022"])

elif globals.IsLinux():
    ret = subprocess.call(["vendor/bin/premake/premake5.linux", "gmake2"])

else:
     ret = subprocess.call(["vendor/bin/premake/premake5", "gmake2"])
     if ret == 0:
         ret = subprocess.call(["vendor/bin/premake/premake5", "xcode4"])

sys.exit(ret)