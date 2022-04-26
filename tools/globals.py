import os

ENGINE_NAME = "GEngine"
PROJECT_NAME = "GEngineEditor"
TOOLS_DIR = "tools"

V_MAJOR = 1
V_MINOR = 0

import sys, platform


#CONFIG = "Debug" 
PLATFORM = sys.platform

for x in platform.uname():
    if "windows" in x.lower():
        PLATFORM = "windows"
        break


def IsWindows():
    return PLATFORM == "windows"


def IsLinux():
    return PLATFORM == "linux"

def IsMac():
    return PLATFORM == "darwin"





  