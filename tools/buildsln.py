import globals
import os, subprocess, sys


#CONFIG = "debug"

args = globals.ProcessArguments(sys.argv)

#print(args)

config = globals.GetArgumentValue(args, "config", "debug")


#CONFIG = globals.ProcessArguments(sys.argv)

#if len(sys.argv) >= 2:
#    CONFIG = sys.argv[1]
    
print("Building config: " + config)
print("\n")

#CONFIG = "Debug" if "-d" in sys.argv else "Release" if "-r" in sys.argv else None



ret = 0

if globals.IsWindows():
    VS_BUILD_PATH = r"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe"
    ret = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(config)])

if globals.IsLinux():
    ret = subprocess.call(["make", "config={}".format(config)])

if globals.IsMac():
    ret = subprocess.call(["make", "config={}".format(config)])

sys.exit(ret)