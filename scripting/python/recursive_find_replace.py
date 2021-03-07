 import os, shutil, ntpath, fileinput, argparse, glob, platform, sys, io
 
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
         replacements = [("$$(DEPS)", "C:/Jenkins/workspace/appname/libs/"),
                         ("$$(APPNAME)", "MYAPP"),
                        ]
     if platform.system() == "Darwin": # MacOS
         replacements = [("$$(DEPS)", "C:/Jenkins/workspace/appname/libs/"),
                         ("$$(APPNAME)", "MYAPP"),
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
