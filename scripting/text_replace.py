import os        # os utils
import shutil    # copy files
import ntpath    # for get path leaf
import fileinput # for text replace
import argparse  # for get command line args
import glob      # get all files in a dir
import platform  # detect os
import sys
import io

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

def text_replace(filepath, text_to_search, replacement_text):
    if os.path.exists(filepath):
        with fileinput.FileInput(filepath, inplace=True) as file:
            for line in file:
                print(line.replace(text_to_search, replacement_text), end='')
    else:
        print("Error: file " + filepath + " not found.")

def alternative_text_replace(filepath, text_to_search, replacement_text):
    if os.path.exists(filepath):
        with io.open(filepath, mode='r', encoding="utf-8") as file:
            filedata = file.read()

        filedata = filedata.replace(text_to_search, replacement_text)

        with io.open(filepath, mode='w', encoding="utf-8") as file:
            file.write(filedata)

if __name__ == '__main__':
    # Get command line args     
    parser = argparse.ArgumentParser()
    parser.add_argument("folder", help="")
    args = parser.parse_args()

    if platform.system() == "Windows":
        replacements = [("$$(DIR)", "C:/path/to/folder/"),
                        ("$$(APP)", "MYAPP"),
                       ]
    if platform.system() == "Darwin": # MacOS
        replacements = [("$$(DIR)", "/path/to/folder"),
                        ("$$(APP)", "MYAPP"),
                       ]

    for original, replacement in replacements:
        for root, dirs, files in os.walk(args.folder):
            for file in files:
                #print("\t" + os.path.join(root, file))
                path = os.path.join(root, file)
                if path.endswith(".pro") or path.endswith(".pri"):
                    print("path: " + path)
                    try:
                        alternative_text_replace(path, original, replacement)
                    except:
                        print("error: " + str(sys.exc_info()[0]))

            #for dir in dirs:
            #    print(os.path.join(root, dir))
