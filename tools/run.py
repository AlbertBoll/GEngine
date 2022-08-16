
import os, subprocess, sys
import globals

args = globals.ProcessArguments(sys.argv)
config = globals.GetArgumentValue(args, "config", "Debug")
prj = globals.GetArgumentValue(args, "prj", globals.PROJECT_NAME)

#CONFIG = "Debug" if "-d" in sys.argv else "Release" if "-r" in sys.argv else None

exepath = "{}/bin/{}/{}/".format(os.getcwd(), config, prj)
ret = 0

if globals.IsWindows():
    #print("Config: {}".format(CONFIG))
    ret = subprocess.call(["cmd.exe", "/c", r"{}\\run.bat".format(globals.TOOLS_DIR), config, prj], cwd=os.getcwd())

else:
    ret = subprocess.call(["{}{}".format(exepath, prj)], cwd=exepath)


sys.exit(ret)