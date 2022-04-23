# cli build
# cli run
# cli gen
# cli version
# cli gen build run

import sys, os
import subprocess

working_directory = os.getcwd();
  
TOOLS_DIR = "tools"

path = os.path.join(working_directory, TOOLS_DIR)

sys.path.append(path)     


import globals
Config = "Debug"

def RunCommand(cmd):
    ret = 0
    script = "{}/{}/{}.py".format(os.getcwd(), TOOLS_DIR, cmd)
    if os.path.exists(script):
        print("Executing: ", cmd)
        ret = subprocess.call(["python", script])
        return ret

    else:
        print("Invalid command: ", cmd)
        ret = -1

    return ret

   
def ChangeConfig_(new_config):
    #globals.CONFIG = new_config
    Config = new_config


#def ChangeConfig():
#    # print(sys.argv)
#    if "-r" in sys.argv:
#        globals.CONFIG = "Release"
#        Config = "Release"
#        print("Change to Release")

#    elif "-d" in sys.argv[0]:
#        globals.CONFIG = "Debug"


print(sys.argv)

for i in range(1, len(sys.argv)):
    
    if "-r" in sys.argv:
        ChangeConfig_("Release")
        #print(globals.CONFIG)
        #globals.CONFIG[0] = "Release"
   

    elif "-d" in sys.argv:
         ChangeConfig_("Debug")
         #globals.CONFIG = "Debug"


    cmd = sys.argv[i]
    if cmd.find("-") == -1:
        print("\n-----------------------------")

        if RunCommand(cmd) != 0:
            break

    #else:
    #    if cmd == "-r":
    #        globals.CONFIG = "Release"

    #    elif cmd == "-d":
    #        globals.CONFIG = "Debug"

        # print("\n-----------------------------")
        

       


