
In my experience it is often easier to use a Docker image for a Tensorflow environment but not always.
It seems as though Nvidia has released a docker image and so has also Google.

The NVidia docker image is biased towards NVidias newer cards and may not work for an older card (even if the card is not that old, if it is not the latest new stuff, this can happen)

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

