
import os, subprocess, sys
import globals

CONFIG = "Debug" if "-d" in sys.argv else "Release" if "-r" in sys.argv else None
exepath = "{}/bin/{}/{}/".format(os.getcwd(), CONFIG, globals.PROJECT_NAME)
ret = 0

if globals.IsWindows():
    print("Config: {}".format(CONFIG))
    ret = subprocess.call(["cmd.exe", "/c", r"{}\\run.bat".format(globals.TOOLS_DIR), CONFIG, globals.PROJECT_NAME], cwd=os.getcwd())

else:
    ret = subprocess.call(["{}{}".format(exepath, globals.PROJECT_NAME)], cwd=exepath)


sys.exit(ret)