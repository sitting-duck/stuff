note: I am always running this in my tensorflow virtual environment on Ubuntu

This script is meant to be used in the situation where you have taken some video and exported it as frames using ffmpeg. 

At this point, I need to go make some test footage using ffmpeg, and I may have lost that command I used to break shit down into frames, damn ;_;


pip install --upgrade scikit-image

pip install --upgrade imutils
pip install imutils

I recall my frame_sequencer.py script was not very robust at all, if it failed on even a single input video it would not recover and I would lose the rest of the night until I restarted it in the morning. My next todo will be to make this script robust

