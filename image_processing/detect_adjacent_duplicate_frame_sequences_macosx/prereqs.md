Environment: I am always running this inside a virtual env with python3 installed on macos 10.14 mojave
I am using pip not anaconda as my package manager. I am always using python3 and pip3

This script is meant to be used in the situation where you have taken some video and exported it as frames using ffmpeg. 

Before running you can install the dependencies you need using these commands: 
```
pip install --upgrade pip # never a bad idea
pip install virtualenv
pip install --upgrade scikit-image
pip install --upgrade imutils
pip install imutils
python3 install -m pip install opencv-python

```

To create new virtual env: python3 -m venv /path/to/new/virtual/environment

the -m flag says: run library module as a script (terminates option list) so it is saying the module we pass to the -m flag is the last option we can pass. We are passing the module venv here, and we are running it as a script. 


