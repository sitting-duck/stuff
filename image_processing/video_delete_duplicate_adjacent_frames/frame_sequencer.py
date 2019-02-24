# HOW TO RUN IN GIT BASH:
# python ./frame_sequencer.py
import os
import subprocess 

# this script will take every video inside the footage folder, make a folder with the same name in the sequenced_footage folder, and inside that folder it just made, 
# it will put all the individual frames of the video. It will run through and do this for every video in the footage folder. 
#
# On error it should just keep going and start on the next video, but this has not been tested yet

videoFolder = "./footage/"
files = os.walk

for root, dirs, files in os.walk(videoFolder):
	for file in files:
		print file
		filename, fileExtension = os.path.splitext(file)
                if not os.path.exists("sequenced_footage/" + filename):
                    os.mkdir("sequenced_footage/" + filename)
                try:
                    # subprocess.check_output(): Run command with arguments and return its output as a byte string.
                    # basically, we just want to print the output
                    # -i: stands for input, we pass the input video file after this flag, (eg. *.mp4, *.mpeg, etc)
                    # -vf specifies that we are using "FilterGraph syntax"
                    # in this case "scale" is the type of filter, and -1:1080 are the arguments to that filter 
                    print subprocess.check_output(['ffmpeg', '-i', videoFolder + file, '-vf', 'scale=-1:1080', '-sws_flags', 'lanczos', videoFolder + '/' + filename + '/' + 'f%07d.png'])
                except subprocess.CalledProcessError as e:
                    print e.output
                    continue

		
