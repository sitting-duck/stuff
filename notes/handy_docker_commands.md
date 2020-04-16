
In my experience it is often easier to use a Docker image for a Tensorflow environment but not always.
It seems as though Nvidia has released a docker image and so has also Google.

The NVidia docker image is biased towards NVidias newer cards and may not work for an older card (even if the card is not that old, if it is not the latest new stuff, this can happen)

Using docker image it is not as easy to have multiple tabs open so one I can use for editing and the other for executing. 

Seems also, I cannot figure out how to do environment stuff like set bashrc, and this makes it difficult to automate stuff for me. Also, the docs on using docker with supervisord were pretty intimidating.

### Loading an Image
You may get an image in to form of a .tar file, in which case you can load it like so: 
```
sudo docker load -i ./myImage.tar

```

Some convenient aliases:
```
alias dattach='sudo docker attach '
alias dimages='sudo docker images '
alias dinfo='sudo docker info '
alias dps='sudo docker ps '
alias drestart='sudo docker restart '
alias drm='sudo docker rm '
alias drun='sudo docker run -shm-size=96g --ulimit memlock=-1 --ulimit stack=-1 -p 6006:6006 -p 6007:6007 -it -v /home/user:/user -v /mnt/ssd:/mnt/ssd -v /mnt/ssd1:/mnt/ssd1 '
```
just refernece here on that run command:
```
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]

--shm-size bytes                 Size of /dev/shm
--ulimit ulimit                  Ulimit options (default [])
-p, --publish list                   Publish a container's port(s) to the host
-i, --interactive                    Keep STDIN open even if not attached
-t, --tty                            Allocate a pseudo-TTY
-v, --volume list                    Bind mount a volume

```

If you are running a fresh docker container you just downloaded, be sure to run ``apt-get update``

```
apt-get update
apt-get install vim
apt install git

#python -m pip install -U pip
pip install --upgrade pip

python -m pip install -U matplotlib
pip install pandas
pip install easydict

apt install libsm6
apt-get install libxrender1
apt-get install libxext6
apt-get install python3-tk
```

### Needed only in 1.9 tf docker container
```
pip install opencv-python
```

### Get Tensorflow 2 with GPU support for Python 3
```
sudo docker pull tensorflow/tensorflow:latest-gpu-py3
```

### Copy Your Files From the Docker Container
```
sudo docker cp  container_name:/path/in/container/ /path/on/host/machine/
```
