I'm trying to install the most up-to-date NVIDIA driver
but when I try to do

```
sudo sh ./NVIDIA-Linux-x86_64-390.48.run
```

an error message appears.

```
ERROR: An NVIDIA kernel module 'nvidia-drm' appears to already be loaded in your kernel.  This may be because it is in use (for example, by an X server, a CUDA program, or
         the NVIDIA Persistence Daemon), but this may also happen if your kernel was configured without support for module unloading.  Please be sure to exit any programs
         that may be using the GPU(s) before attempting to upgrade your driver.  If no GPU-based programs are running, you know that your kernel supports module unloading,
         and you still receive this message, then an error may have occured that has corrupted an NVIDIA kernel module's usage count, for which the simplest remedy is to
         reboot your computer.
```

When I try to find out who is using nvidia-drm (or nvidia_drm), I see nothing.

```
~$ sudo lsof | grep nvidia-drm
lsof: WARNING: can't stat() fuse.gvfsd-fuse file system /run/user/1000/gvfs
      Output information may be incomplete.
~$ sudo lsof -e /run/user/1000/gvfs | grep nvidia-drm
~$
```

And when I try to remove it, it says it's being used.

```
~$ sudo modprobe -r nvidia-drm
modprobe: FATAL: Module nvidia_drm is in use.
~$ 
```

We want to stop the display manager which is using the NVIdia drivers.

Change to a text console prssing ctrl + alt + f2 and logging in as root. Use this command to disable the graphical target, what is what keeps the display manager running:
```
# systemctl isolate multi-user.target
```

Now you can unload the Nvidia drivers using ``modprobe -r``
```
# modprobe -r nvidia-drm
```

Now you can actually run your ``.run`` file Nvidia driver installer, and start the graphical environment again.
```
# systemctl start graphical.target
```

