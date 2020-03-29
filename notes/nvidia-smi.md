
Operating System: Ubuntu


Your nvidia-smi output should look something like this:

```
+-----------------------------------------------------------------------------+          
| NVIDIA-SMI 430.40       Driver Version: 430.40       CUDA Version: 10.1     |          
|-------------------------------+----------------------+----------------------+          
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |          
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |          
|===============================+======================+======================|          
|   0  TITAN RTX           Off  | 00000000:0C:00.0 Off |                  N/A |          
| 48%   55C    P0    75W / 280W |      0MiB / 24220MiB |      1%      Default |          
+-------------------------------+----------------------+----------------------+          
|   1  TITAN RTX           Off  | 00000000:41:00.0 Off |                  N/A |          
| 26%   54C    P0     1W / 280W |      0MiB / 24217MiB |      0%      Default |          
+-------------------------------+----------------------+----------------------+          
                                                                                         
+-----------------------------------------------------------------------------+          
| Processes:                                                       GPU Memory |          
|  GPU       PID   Type   Process name                             Usage      |          
|=============================================================================|          
|  No running processes found                                                 |          
+-----------------------------------------------------------------------------+       

```

If it doesn't, something might be off. 

If you can't invoke nvidia-smi you need to go get the NVidia driver installer in the form of a ``.run`` file installer and run it. 
You may periodically have to redo this actually until you figure out how to get the kernel not to shed certain changes on restart. 

It seems like on restart you will just have to randomly redo this, so SAVE THAT .RUN FILE SOMEWHERE SAFE
because you know it was a working configuration before, 
if you try the latest installer and nothing works you'll be in deep trouble.

Note: in your Python code, it seems like once you get
```
2019-09-19 16:07:09.367382: W tensorflow/compiler/xla/service/platform_util.cc:256] unabl
e to create StreamExecutor for CUDA:0: failed initializing StreamExecutor for CUDA device
 ordinal 0: Internal: failed call to cuDevicePrimaryCtxRetain: CUDA_ERROR_OUT_OF_MEMORY:
out of memory; total memory reported: 25396838400
2019-09-19 16:07:09.367581: F tensorflow/stream_executor/lib/statusor.cc:34] Attempting t
o fetch value instead of handling error Internal: no supported devices found for platform
 CUDA
```

there is no recovering your script, you're better off just calculating what you can load into memory ahead of time and never exceeding that. 
This isn't something you can just ``try catch``

Monitor ``nvidia-smi`` in a separate terminal window to monitor how your script is doing. If it keeps bouncing up and down between extreme values like near zero and near 100 percent, your script is not optimized well, 
when it is at zero percent your script is running on the CPU and when it is at the high percentage, your script is running on the GPU. 

The processes section at the bottom will actually show you which pids are running on which card, but it doesn't seem granular enough to show you new processes you have launched using the ``multiprocessing`` module in python.

This shows us one side of the equation, the GPU, but nothing about the CPU. 

You can see what's going on on the CPU using the ``htop`` command.

