import urllib.request
import os.path
from os import path

import html2text

url = 'https://www.huffpost.com/entry/weird-fathers-day-gifts-2018_n_5b05bf18e4b05f0fc84438f6'

class AppURLopener(urllib.request.FancyURLopener):

    version = "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.69 Safari/537.36"

### main

urllib.request = AppURLopener()

# fail
#with urllib.request.retrieve(url) as f:
#    print(f.read().decode('utf-8'))


# open get.sh
file = open("get.sh", "r")
lines = file.readlines()

for line in lines:
    line = line.replace("wget ", "") # strip wget so it is just straight web url
    line = line.replace('"', '')
    line = line.replace('\n', '')

    print("retrieve " + line)

    filename = line.replace("https://www.huffingtonpost.com/entry/", "")

    if path.exists("../articles/" + filename + ".html") == False: # check to see if we downloaded this one already
        # if we haven't downloaded and processed this one before we proceed
        try: 
            urllib.request.retrieve(line, "../articles/" + filename + ".html") # get the article and save as html file in articles folder
        except: 
            print("fail") 
            continue


        h = html2text.HTML2Text()
        # Ignore converting links from HTML
        h.ignore_links = True
        h.ignore_images = True

        # get the contents of the html file
        html_file = open("../articles/" + filename + ".html")
        contents = html_file.read()
        html_file.close()


        text_only = h.handle(contents)

        text_out = open("../text/" + filename + ".txt", "w")

        text_out.write(text_only)
        text_out.close()





