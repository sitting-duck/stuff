
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
```bash
alias dattach='sudo docker attach '
alias dimages='sudo docker images '
alias dinfo='sudo docker info '
alias dps='sudo docker ps '
alias drestart='sudo docker restart '
alias drm='sudo docker rm '
alias drun='sudo docker run -shm-size=96g --ulimit memlock=-1 --ulimit stack=-1 -p 6006:6006 -p 6007:6007 -it -v /home/user:/user -v /mnt/someFolder1:/mnt/someFolder1 -v /mnt/someFolder2:/mnt/someFolder2 '
```
just reference here on that run command:
```
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]

--shm-size bytes                 Size of /dev/shm
--ulimit ulimit                  Ulimit options (default [])
-p, --publish list                   Publish a container's port(s) to the host
-i, --interactive                    Keep STDIN open even if not attached
-t, --tty                            Allocate a pseudo-TTY
-v, --volume list                    Bind mount a volume

```


### Create new tmux session
```bash
tmux new -s session_name
# ctrl + bd to detach from session (without ending session)
```

### Install
```bash
sudo apt-get remove docker docker-engine docker.io containerd runc
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
```

### Get Tensorflow 2 with GPU support for Python 3
```bash
sudo docker pull tensorflow/tensorflow:1.9.0-devel-gpu-py3 # TF 1.9
sudo docker pull tensorflow/tensorflow:latest-gpu-py3
```

### Copy Your Files From the Docker Container
```
sudo docker cp  container_name:/path/in/container/ /path/on/host/machine/
```
