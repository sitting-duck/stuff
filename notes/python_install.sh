

# If you are running a fresh docker container you just downloaded, be sure to run ``apt-get update``
```
export PYTHONPATH=$PYTHONPATH:/usr/lib/python3.
alias python='python3'
alias pip='pip3'


apt install python3-pip
pip install --upgrade pip

pip install opencv-python
python -m pip install -U matplotlib
pip install pandas
pip install easydict

apt install libsm6
apt-get install libxrender1
apt-get install libxext6
apt-get install python3-tk
pip install imageio
pip install numpy
pip install scipy

#pip uninstall tensorlayer
#pip install tensorlayer==1.11.1
pip install git+https://github.com/JiahuiYu/neuralgym
pip install pyyaml
pip install --upgrade cython
```
```
Older versions of TensorFlow

For releases 1.15 and older, CPU and GPU packages are separate:

pip install tensorflow==1.15      # CPU
pip install tensorflow-gpu==1.15  # GPU

# Jupyter 
# If installing using pip install --user, you must add the user-level bin directory to your PATH environment variable in order to launch jupyter lab. 
# If you are using a Unix derivative (FreeBSD, GNU / Linux, OS X), you can achieve this by using export PATH="$HOME/.local/bin:$PATH" command.

```
