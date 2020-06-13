
You can pass --extract to your installer to get the three installers out o fi t. 

1. An NVidia driver install but usually of a stale version 
2. the actual Cuda installer
3. The Cuda samples installer

Just extract these separately so you don't have to fuss with th stuff you don't care about. 

```bash
These are the dirs where Cuda is stored: 
/usr/bin/bin2c
/usr/bin/cudafe
/usr/bin/cudafe++
/usr/bin/cuda-gdb
/usr/bin/cuda-memcheck
/usr/bin/cuobjdump
/usr/bin/fatbinary
/usr/bin/nvcc
/usr/bin/nvlink
/usr/bin/nvprof
/usr/bin/nvvp
/usr/bin/ptxas
```
Make sure that these things are true:
```bash
Creating symbolic link /usr/local/cuda -> /usr/local/cuda-9.0

========================================

Please make sure that
 -   PATH includes /usr/local/cuda-9.0/bin
 -   LD_LIBRARY_PATH includes /usr/local/cuda-9.0/lib64, or, add /usr/local/cuda-9.0/lib64 to /etc/ld.so.conf and run ldconfig as root

Please read the release notes in /usr/local/cuda-9.0/doc/
To uninstall the CUDA Toolkit, run the uninstall script in /usr/local/cuda-9.0/bin

```

### NVidia SMI is reporting a different  Cuda version than what I installed:
The nvidia-smi tool gets installed by the GPU driver installer, and generally has the GPU driver in view, not anything installed by the CUDA toolkit installer.

Recently (somewhere between 410.48 and 410.73 driver version on linux) the powers-that-be at NVIDIA decided to add reporting of the CUDA Driver API version installed by the driver, in the output from nvidia-smi.

This has no connection to the installed CUDA runtime version.

nvcc, the CUDA compiler-driver tool that is installed with the CUDA toolkit, will always report the CUDA runtime version that it was built to recognize. It doesn't know anything about what driver version is installed, or even if a GPU driver is installed.

```bash
## ImportError: libcuda.so.1: cannot open shared object file: No such file or directory

# Solved via: 
ln -s /usr/local/cuda/lib64/stubs/libcuda.so /usr/local/nvidia/lib64/libcuda.so.1
```

```
# Start a GPU enabled container on two GPUs
docker run --gpus 2 nvidia/cuda:10.0-base nvidia-smi

wget http://us.download.nvidia.com/XFree86/Linux-x86_64/440.82/NVIDIA-Linux-x86_64-440.82.run
```
