import globals
import os, sys
import subprocess

args = globals.ProcessArguments(sys.argv)
prj = globals.GetArgumentValue(args, "prj", globals.PROJECT_NAME)

ret = 0

if globals.IsWindows():
    rundir = "{}/{}/".format(os.getcwd(), prj)
    print(rundir)
    ret = subprocess.call(["cmd.exe", "/c", "mklink", "/D", "projlink", prj+"\\"], cwd=os.getcwd())
else:
    print("No symlink necessary")
sys.exit(ret)