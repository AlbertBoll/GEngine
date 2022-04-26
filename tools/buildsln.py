import globals
import os, subprocess, sys

ret = 0


CONFIG = "Debug" if "-d" in sys.argv else "Release" if "-r" in sys.argv else None

if globals.IsWindows():
    VS_BUILD_PATH = r"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe"
    ret = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(CONFIG)])

if globals.IsLinux():
    ret = subprocess.call(["make", "config={}".format(CONFIG.lower())])

if globals.IsMac():
    ret = subprocess.call(["make", "config={}".format(CONFIG.lower())])

sys.exit(ret)