

Upgrade
Ashley Tharp
Analytics Vidhya
ABOUT US
MACHINE LEARNING
DEEP LEARNING
HACKATHONS
CONTRIBUTE
FREE COURSES
Installing OpenCV 3 from Source on macOS Catalina
A K Dash
A K Dash
Follow
Oct 27, 2019 · 6 min read




Photo by Thomas Q on Unsplash

OpenCV has become one of the most widely used open-sourced library used in the field of computer vision. Thanks to the volunteers who have contributed to this library. The journey from Willow Garage to opencv.org has been inspiring. However, setting up the environment to build OpenCV from source is always challenging. With every new release as well as with a new operating system release, configuring OpenCV will be cumbersome.
In this blog post, I am going to note down the OpenCV build process in baby steps on recently released macOS Catalina. Dropping the support for 32-bit applications has created an unpleasant situation amongst some users.
Prerequisites before starting the build process
You need to install python as we are not going to mess with the system python. For this blog post, I am going to use python 3.6. Download it from its official site and install it. Given below are the steps you need to follow to build OpenCV on macOS Catalina.
1. Install and Configure Xcode
Download Xcode from App Store. It will take a while as the size of this file is nearly 7 to 8 GB. After the successful installation of Xcode, run the following command.
$ sudo xcodebuild -license
Use the space key to move to the bottom of the agreement page and type [accept] to agree with the license. Next, we need to install the command line tools, which will install the basic compilers (gcc, g++, etc.). Use the command given below.

$ sudo ``xcode-select --install``
2. Install homebrew for MacOS Catalina
To install homebrew, visit their official site [ link ]. Run the following code from the terminal to install.
```$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"```
After installing homebrew, update the package definition.
```$ brew update```
[Note] Run the ``$ echo $PATH`` command in the terminal to check if ``/usr/local/bin`` has been added to the system’s path. If it has not been added, update the bash_profile or bashrc or zshrc (based on your system) and add the following lines to the file. As I am using iTerm2 as my terminal replacement, in the following command, I will update ~/.zshrc file.You can use any editor of your choice.
```$ vim ~/.zshrc```
Append the following lines to the file and save it.
```# Homebrew
export PATH=/usr/local/bin:$PATH```
Reload the ~/.zshrc file using source command.
```$ source ~/.zshrc```
3. Install Python 3.6 from the official site
After installing the downloaded python file, run the following command to check the path of python3.
```$ which python3
/Library/Frameworks/Python.framework/Versions/3.6/bin/python3
$ python3 --version
Python 3.6.8```
Using the brew package manager, install the following dependencies for building OpenCV.
```$ brew install cmake pkg-config wget
$ brew install jpeg libpng libtiff openexr
$ brew install eigen tbb hdf5```
4. Create the python virtual environment
The next step is to install virtualenv and virtualenvwrapper using pip.
$ pip3 install virtualenv virtualenvwrapper
Configure the ~/.zshrc profile page again to set the environment variables.
```# virtualenv and virtualenvwrapper
export VIRTUALENVWRAPPER_PYTHON=/Library/Frameworks/Python.framework/Versions/3.6/bin/python3
source /Library/Frameworks/Python.framework/Versions/3.6/bin/virtualenvwrapper.sh```
After updating the ~/.zshrc file, reload it by using the source command.
$ source ~/.zshrc
Create a virtual environment with the name py3cv3. You can choose a suitable name for your needs.
```$ mkvirtualenv py3cv3 -p python3```
5. Installing Opencv 3.4.7 from Source
The only python dependency required by OpenCV is NumPy (we will use 1.14.0), which we can install by using the following command.
```$ workon py3cv3
$ pip install numpy==1.14.0```
Let us compile OpenCV from the source. First, we have to download the source code for opencv and opencv_contrib ( we will use version 3.4.7). You can use the version according to your requirements. After downloading the source, we will unpack it and store them inside the home folder.
```$ cd ~
$ wget -O opencv.zip https://github.com/opencv/opencv/archive/3.4.7.zip
$ wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/3.4.7.zip
$ unzip opencv.zip
$ unzip opencv_contrib.zip```
We will rename the extracted folder so that the version information would be removed from the extracted folder name.
```$ mv opencv-3.4.7 opencv
$ mv opencv_contrib-3.4.7 opencv_contrib```
We will use CMake to run the build process from the source [1].
```$ cd ~/opencv
$ mkdir build
$ cd build
$ cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D PYTHON3_LIBRARY=`python -c 'import subprocess ; import sys ; s = subprocess.check_output("python-config --configdir", shell=True).decode("utf-8").strip() ; (M, m) = sys.version_info[:2] ; print("{}/libpython{}.{}.dylib".format(s, M, m))'` \
    -D PYTHON3_INCLUDE_DIR=`python -c 'import distutils.sysconfig as s; print(s.get_python_inc())'` \
    -D PYTHON3_EXECUTABLE=$VIRTUAL_ENV/bin/python \
    -D BUILD_opencv_python2=OFF \
    -D BUILD_opencv_python3=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D INSTALL_C_EXAMPLES=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D BUILD_EXAMPLES=ON ..```
Check for the output of CMake. It should look as follows:
Check the interpreter and numpy library path. It should be selected from the virtual environment
Run the following code to make from the build files.
```$ make -j4```
After a successful make, we can install it by using the following command.
```$ sudo make install```
To check the successful installation inside the system, you can search for the “opencv.pc” configuration file. Generally, it can be found in the following path.
``/usr/local/lib/pkgconfig/opencv.pc``
Run the following command to check the installed version.
```$ pkg-config --modversion opencv
3.4.7
```$ pkg-config --libs --cflags opencv
-I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_highgui -lopencv_videoio -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core```
After the installation, we have to create a symbolic link of the cv2.so file into the virtual environment. Let’s first check whether the .so file exists inside the installation path or not.
```$ cd /usr/local/lib/python3.6/site-packages/cv2/python-3.6
$ ls
cv2.cpython-36m-darwin.so```
If we want to install multiple versions of OpenCV, its better to rename it, to avoid any confusion with later installations. After renaming, we can create the symbolic link of the .so file into the virtual environment (e.g., py3cv3).
```$ sudo mv cv2.cpython-36m-darwin.so cv2.opencv3.4.7.so
$ cd ~/.virtualenvs/py3cv3/lib/python3.6/site-packages
$ ln -s /usr/local/lib/python3.6/site-packages/cv2/python-3.6/cv2.opencv3.4.7.so cv2.so```
Finally, we can test the installation by running the following commands.
```$ cd ~
$ workon py3cv3
$ python
>>> import cv2
>>> cv2.__version__
'3.4.7'```
If you are able the see the version of OpenCV, the installation has been successful in your system, and you are ready to go. Congratulations!!
6. Tensorflow and Keras Installation on macOS Catalina
We are going to install TensorFlow and Keras inside the virtual environment py3cv3. To activate the virtual environment, just run the following code.
```$ workon py3cv3```
Using pip, we will install some of the famous computer vision, machine learning, and image processing packages.
```$ pip install scipy pillow
$ pip install imutils h5py requests progressbar2
$ pip install scikit-learn scikit-image```
Next, we will install matplotlib and update the rendering background.
```$ pip install matplotlib
$ mkdir ~/.matplotlib
$ vim ~/.matplotlib/matplotlibrc
$ echo "backend: TkAgg" >> ~/.matplotlib/matplotlibrc```
If you ever face any difficulties in getting a final output in matplotlib, follow the official documentation page to set up the virtual environment for matplotlib [Link]. Now it’s the time to install TensorFlow and Keras. Follow the TensorFlow APIs page to select the required version. I am using version r1.15 here.
```$ pip install tensorflow==1.15
$ pip install keras
$ python
>>> import tensorflow as tf
>>> tf.__version__
'1.15.0'
>>> import keras```
Using TensorFlow backend.
The Keras configuration file is present inside the home folder with a path ~/.keras/keras.json. You can open the file to have a look into the contents. Make sure the “image_data_format” field is set to channels_last and that the “backend” is set to tensorflow.
Congratulations!! You have successfully installed OpenCV on the macOS Catalina.
References
1. https://www.pyimagesearch.com/2019/01/30/macos-mojave-install-tensorflow-and-keras-for-deep-learning/
Analytics Vidhya
Analytics Vidhya is a community of Analytics and Data…
Following
24

Python
Opencv 3
Macos Catalina

24 claps

Applause from you and 3 others



A K Dash
WRITTEN BY

A K Dash
Follow
Analytics Vidhya
Analytics Vidhya
Following
Analytics Vidhya is a community of Analytics and Data Science professionals. We are building the next-gen data science ecosystem https://www.analyticsvidhya.com
Write the first response
More From Medium
More from Analytics Vidhya
Your Ultimate Python Visualization Cheat-Sheet
Andre Ye in Analytics Vidhya
May 10 · 6 min read
266

More from Analytics Vidhya
Calculus and Algebra in Python just became so much easier
Sohit Miglani in Analytics Vidhya
May 5 · 9 min read
248

More from Analytics Vidhya
Forecast the Likes on my Facebook Fan Page — Can I Reach 100k Likes in 6 months?
Eric Weng in Analytics Vidhya
May 11 · 7 min read
508

Discover Medium
Welcome to a place where words matter. On Medium, smart voices and original ideas take center stage - with no ads in sight. Watch
Make Medium yours
Follow all the topics you care about, and we’ll deliver the best stories for you to your homepage and inbox. Explore
Become a member
Get unlimited access to the best stories on Medium — and support writers while you’re at it. Just $5/month. Upgrade
About
Help
Legal