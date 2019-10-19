
### Building the Tensorflow Source code on Windows in C++ with GPU support

### Step 0: Check your hardware
Before we even start we need to make sure you are running on the correct hardware. See below this screencap from the Tensorflow documentation:
![Hardware reqs](hardware_reqs.png)
That links to here: ``https://developer.nvidia.com/cuda-gpus``. You'll be able to find your card from there. 

At this time (10/11/2019), you need an NVidia GPU. You normally will not get these in a laptop unless it is a gaming laptop.  
From the documentation on ``https://www.tensorflow.org/install/gpu``
![How to Find out What GPU You Have](how_to_find_out_what_gpu_i_have.png)

Alternatively, you can also look under Display Adaptors in the Device Manager: 
For example I checked my device manager under display adaptors to see what graphics card I have: 
![Check graphics card](device_manager_check_graphics_card.png)

### Step 1: Install NVidia Graphics Card Driver
You need to install the NVidia graphics driver for your card.
The page for NVidia Graphics card drivers is ``https://www.nvidia.com/Download/index.aspx``

And you're going to find your graphics card using this form:
![NVidia Driver Download Form](nvidia_driver_downloads.png)

If you use that form, you are guaranteed to download the latest version, if you just google for your card and find a link to an older version of the driver, if you are lucky, when you run and install, you may see an error like this if your driver is too old:

![Incompatible Graphics Hardware](incompatible_graphics_hardware.png)
But you might not be so lucky and have to find out later. So use that form, I have made the mistake before of just using some link I found on StackOverflow and installed a driver that was outdated. Don't make my mistake :)

If you don't see your graphics card in there, keep looking, you are possibly looking under the wrong category. If it is an NVidia graphics card and it exists, it will be in there somewhere. If you go throiugh this form you are guaranteed to get the latest version. 

You will download an exe file and run it to install your NVidia graphics card driver. The one I ended up using was: ``http://us.download.nvidia.com/Windows/436.48/436.48-notebook-win10-64bit-international-whql.exe``

### Step 2: Install Cuda for Windows
The documentation is here: ``https://docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows/`` <br>
Go to here: ``https://developer.nvidia.com/cuda-downloads`` and download the NVidia Cuda Toolkit. <br>

![Download Cuda Enabled toolkit](download_cuda_enabled_toolkit.png)

### Step 3: Install Python for Windows
Download page: ``https://www.python.org/downloads/windows/``
Make sure you set your path variables. If you cannot call ``python --version`` from the ``cmd`` terminal you did not set your environment variables correctly yet.
![Into Build from Source](intro_build_from_source.png)

Once you have installed Python for Windows, also install those dependencies in the screencap above.

### Step 3: Install Bazel
The documentation is on this page: ``https://docs.bazel.build/versions/master/install-windows.html``
Follow all the steps on that page and install all the prereqs.

Then you will go to this page to actually install Bazel: ``https://github.com/bazelbuild/bazel/releases/tag/0.24.1`` There are more recent versions, but 0.24 is the version you need for building Tensorflow 1.14 on Windows.

If you install the wrong version you will see something like this: 
![Wrong version Bazel](wrong_version_bazel.png)
The first time you try to build tensorflow, so make sure you have downloaded version 0.24.

### Step 4: Configure Bazel to Build C++ on Windows
Follow this documentation: ``https://docs.bazel.build/versions/master/windows.html#build-c-with-msvc``

### Step 4: Install MSYS
Go here: ``https://www.msys2.org/`` and download and install MSYS for the bin tools you will need to build Tensorflow

If MSYS2 is installed to ``C:\msys64``, ie. you installed the 64 bit version, add ``C:\msys64\usr\bin`` to your ``%PATH%`` environment variable. Then, using cmd.exe, run:
```
pacman -S git patch unzip
```

### Step 5: Install Visual Studio Build Tools 2017
Documentation is here: ``https://www.tensorflow.org/install/source_windows#install_visual_c_build_tools_2017``
Note: I have done this with MSVC 2015 with no problems, so that might work for you too.

### Step 6: Clone the Tensorflow source code
Original Documentation: ``https://www.tensorflow.org/install/source_windows#download_the_tensorflow_source_code``

``cd`` into your cloned directory and do ``git checkout r1.14``

### Step 7: Configure the Build using configure.py
Original Documentation: ``python ./configure.py``
Run ``python ./configure.py`` at the root of your source tree

You will probably want to say no to all the other dependencies it asks you about (unless you are specifically aware that your project needs it), but you should say yes when it asks you if you want to build with Cuda. A successful session will look something like this: 
```
$ python configure.py
WARNING: --batch mode is deprecated. Please instead explicitly shut down your Bazel server using the command "bazel shutdown".
You have bazel 0.24.1 installed.
Please specify the location of python. [Default is C:\Users\Username\AppData\Local\Programs\Python\Python36\python.exe]:


Found possible Python library paths:
  C:\Users\Username\AppData\Local\Programs\Python\Python36\lib\site-packages
Please input the desired Python library path to use.  Default is [C:\Users\Username\AppData\Local\Programs\Python\Python36\lib\site-packages]

Do you wish to build TensorFlow with XLA JIT support? [y/N]:
No XLA JIT support will be enabled for TensorFlow.

Do you wish to build TensorFlow with ROCm support? [y/N]:
No ROCm support will be enabled for TensorFlow.

Do you wish to build TensorFlow with CUDA support? [y/N]: Y
CUDA support will be enabled for TensorFlow.

Found CUDA 10.0 in:
	C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/lib/x64
	C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/include
Found cuDNN 7 in:
	C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/lib
	C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/include

``` 

### Step 7: Build the dll 
Note: Dont do this:
```
bazel build //tensorflow/tools/pip_package:build_pip_package
```
This is on the ``https://www.tensorflow.org/install/source_windows`` but this is building Python stuff, you don't want that. You want the C++ API for tensorflow so disregard that.

```
bazel build --config=cuda tensorflow:tensorflow.dll
```
The build will take a long time (possibly between 20 minutes and an hour the first time)

### Step 8: Build the .lib
```
bazel build --config=cuda tensorflow:tensorflow.lib
```
The build may take a long time (possibly between 20 minutes and an hour the first time)

### Step 8: Link your .lib into your Windows project for testing
You may do this in Visual Studio, or Qt for example. Add a path to your .lib file and test compilation calling a tensorflow function in your c++.

### Step 9: Add Header source if necessary
On my build I had trouble with these libs so I downloaded their source code separately and linked them into my project. <br>
Clone these header libraries from Github or download the source from these 3 places: 
```
https://github.com/protocolbuffers/protobuf/releases/tag/v3.7.0 
https://github.com/abseil/abseil-cpp 
http://eigen.tuxfamily.org/index.php?title=Main_Page 
``` 
and link them into your Windows project if you are having trouble with missing header files or recursive includes of headers in the eigen library.


### Step 9: Identify Missing Symbols:
You have built your .libs and .dll files. Now you should make a small C++ project to test using these libraries. Probably one of the first things you will want to do is just some very very basic tensorflow setup code like this: 
```
#include "tensorflow/cc/ops/standard_ops.h"
#include <tensorflow/core/framework/graph.pb.h>
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/protobuf/meta_graph.pb.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/framework/tensor.h"

using namespace tensorflow;

int main(int argc, char *argv[]) {
	// Create a Session running TensorFlow locally in process.
	std::unique_ptr<tensorflow::Session> session(tensorflow::NewSession({}));

	return 0;
}
```

Probably you will see some complaints about unresolved external symbols like this:
For each compilation error you see like this: 
![unresolved external symbol](unresolved_external_symbol.png)


Go to the source code that has the missing symbol error. In your IDE you may be able to right click the symbol reference in your actual code and select "Go to Symbol Definition" or something similiar. 
I am using Qt Creator for my C++ project code and it looks like this: 
![Right click and select go to symbol definition](find_symbol_in_editor.png)

This will take you into somewhere in the actual tensorflow source code. In front of the function definition or the class definition that caused the missing symbol error put the macro ``TF_EXPORT``, at the top of that same file, before any other includes put ``#include "tensorflow/core/platform/macros.h"`` 

![add TF_EXPORT to symbol](add_tf_export_to_symbol.png)
![add_path_to_macros](add_path_to_macros.png)

and then rebuild your .lib. Tensorneeds to be built with that symbol exported. Just calling ``bazel build --config=cuda tensorflow:tensorflow.lib`` will suffice, there is no need to do a clean rebuild.



