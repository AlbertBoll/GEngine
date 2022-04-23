
#from globals import CONFIG
import globals
#from ... import cli

import os, subprocess, sys
sys.path.append(os.getcwd())    
import cli

print(cli.Config)
#cli.ChangeConfig()
# config = globals.CONFIG
exepath = "{}/bin/{}/{}/".format(os.getcwd(), globals.CONFIG, globals.PROJECT_NAME)
ret = 0

if globals.IsWindows():
    print("Config: {}".format(globals.CONFIG))
    ret = subprocess.call(["cmd.exe", "/c", r"{}\\run.bat".format(globals.TOOLS_DIR), globals.CONFIG, globals.PROJECT_NAME], cwd=os.getcwd())

else:
    ret = subprocess.call(["{}{}".format(exepath, globals.PROJECT_NAME)], cwd=exepath)

print(cli.Config)
sys.exit(ret)