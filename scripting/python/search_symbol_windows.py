# Windows only script utility for searching a folder for a .lib containing symbolname

# This script will recursively search the folder passed into the sript with the argument "folder",
# and for every .lib file found, it will invoke DUMPBIN, a Microsoft built in utility, 
# to print out all the symbols in the .lib file, 
# if the symbol name (or part of it) is a match for the "original string" argument that you passed in
# it will print out to the command line
# so any symbols with a complete or with a substring match will print out for you,
# I find this very useful for troubleshooting "Unresolved External Symbol" Errors in C++

# run this in vstudio 2019 developer console as administrator 
import os, shutil, ntpath, fileinput, argparse, glob, platform, sys, io, subprocess



if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("folder", help="Folder to recursively search")
    parser.add_argument("symbol", help="original string")
    args = parser.parse_args()

    for root, dirs, files in os.walk(args.folder):
        for file in files:
            #print("\t" + os.path.join(root, file))
            path = os.path.join(root, file)
            if path.endswith(".lib"):
                print("lib: " + path)

                result = subprocess.run(["dumpbin", "/SYMBOLS", path], stdout=subprocess.PIPE)
                
#                lines = str(result.stdout).getlines()
                lines = result.stdout.split(b'\n')

                print("numlines: " + str(len(lines)))
                for line in lines:
                    if args.symbol in str(line):
                        print("got: " + str(line))
                
