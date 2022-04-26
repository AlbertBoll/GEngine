# cli build
# cli run
# cli gen
# cli version
# cli gen build run

import sys, os
import subprocess

working_directory = os.getcwd();
  
TOOLS_DIR = "tools"

Config = "Debug" if "-d" in sys.argv else "Release" # if "-r" in sys.argv else None



def RunCommand(cmd, arg=""):
    ret = 0
    script = "{}/{}/{}.py".format(os.getcwd(), TOOLS_DIR, cmd)
    if os.path.exists(script):
        print("Executing: ", cmd)
        ret = subprocess.call(["python", script, arg])
        return ret

    else:
        print("Invalid command: ", cmd)
        ret = -1

    return ret


def CaptureArg():
    if "-d" in sys.argv:
        return "-d"  #Debug
    elif "-r" in sys.argv:
        return "-r"  #Release

    else:
        return ""



if __name__ == "__main__":

    arg = CaptureArg() 
    length = len(sys.argv) - 1 if "-" in sys.argv[-1] else len(sys.argv) 
    for i in range(1, length):
        
        cmd = sys.argv[i]
       
        print("\n-----------------------------")

        if RunCommand(cmd, arg) != 0:
            break

        

       


