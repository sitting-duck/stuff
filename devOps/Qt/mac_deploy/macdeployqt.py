import os         # os utils
import shutil     # copy files
import ntpath     # for get path leaf
import fileinput  # for text replace
import argparse   # for get command line args
import glob       # get all files in a dir
import platform   # detect os
import subprocess # for making command line calls

if __name__ == '__main__':

    # Get command line args     
    parser = argparse.ArgumentParser()
    parser.add_argument("PACKAGING_DIR", help="a dir where all the assets are thrown together to package into the installer")
    parser.add_argument("FULLNAME", help="eg. Topaz Video Enhance AI || Topaz Video Enhance AI (BETA)")
    args = parser.parse_args()

    # first make a copy of the executable
    exec_dir = args.PACKAGING_DIR + "/" + args.FULLNAME + ".app/Contents/MacOS/"
    orig = args.PACKAGING_DIR + "/" + args.FULLNAME + ".app/Contents/MacOS/Topaz Video Enhance AI" 
    backup = orig + " backup"
    shutil.copyfile(orig, backup)

    # list the dir contents so we can confirm via the Jenkins console if needed
    print("after make a backup")
    os.listdir(exec_dir)

    # for each @rpath in the install names we are going to remove it
    o = subprocess.Popen(['/usr/bin/otool', '-L', orig], stdout=subprocess.PIPE)

    for line in o.stdout:
        line = str(line)
        line = line.replace("\\t", "")
        line = line.replace("\\n", "")
        in_between_parens = line[line.find("(")+1:line.find(")")]
        line = line.replace(in_between_parens, "")
        line = line.replace("(", "")
        line = line.replace(")", "")        
        line = line.replace(" ", "")

        
        #io = subprocess.Popen(["/usr/bin/install_name_tool", "-change", line, line.replace("@rpath", ""), "'"+orig+"'"], shell=True,  stdout=subprocess.PIPE)
        io = os.system("sudo /usr/bin/install_name_tool -change '" + line + "' '" + line.replace("@rpath", "") + "' '" + orig + "'")

    print("after install_name_tool to remove @rpath")
    o2 = subprocess.Popen(['/usr/bin/otool', '-L', orig], stdout=subprocess.PIPE)
    for line in o2.stdout:
        print(line)

