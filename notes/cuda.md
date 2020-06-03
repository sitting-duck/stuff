
You can pass --extract to your installer to get the three installers out o fi t. 

1. An NVidia driver install but usually of a stale version 
2. the actual Cuda installer
3. The Cuda samples installer

Just extract these separately so you don't have to fuss with th stuff you don't care about. 

```
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
```
Creating symbolic link /usr/local/cuda -> /usr/local/cuda-9.0

========================================

Please make sure that
 -   PATH includes /usr/local/cuda-9.0/bin
 -   LD_LIBRARY_PATH includes /usr/local/cuda-9.0/lib64, or, add /usr/local/cuda-9.0/lib64 to /etc/ld.so.conf and run ldconfig as root

```

