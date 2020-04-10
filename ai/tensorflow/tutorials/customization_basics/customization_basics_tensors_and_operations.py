import tensorflow as tf

# as of tensorflow 2, eager execution is turned on by default. This enables a more interactive frontend to Tensorflow, the details of which we will discuss much later. 

import tensorflow as tf

### Tensors 
# A tensor is a multi dimensional array. Similar to Numpy ndarray objects, tf.Tensor objects have a data type and a shape. 
# Additionally, tf.Tensors can reside in accelerator memory (like a GPU). Tensorflow offers a rick library of operations
# (tf.add, tf.matmul, tf.linalg.inv etc) that consume and produce tf.Tensors. These oprations automatically convert native Python types

# The most obvious differences between NumPy arrays and tf.Tensors are:
# 1. Tensors can be backed by accelerator memory (like GPU, TPU)
# 2. Tensors are immutable

### Numpy Compatibility
# Converting between a Tensorflow tf.Tensors and a NumPy ndarray is easy:
# TensorFlow operations automatically convert Nympy ndarrays to Tensors.
# Numpy operations automatically convert Tensors to NumPy ndarrays

# Tensors are explicitly converted to NumPy ndarrays using their .numpy() method. 
# These conversions are typically cheap since the array and tf.Tensor share the underlying memory representation, if possible. 
# However, sharing the underlying representation isn't always possible since the tf.Tensor may be hosted in GPU memory while NumPy arrays are always backed by host memory, and the conversion
# involves a copy from GPU to host memory.

import numpy as np

ndarray = np.ones([3, 3])

print("Tensorflow operations convery numpy arrays to Tensors automatically")
tensor = tf.multiply(ndarray, 42)
print(tensor)

print("And NumPy operations convert Tensors to numpy arrays automatically")
print(np.add(tensor, 1))

print("The .numpy() method explicityly converts a Tensor to a numpy array")
print(tensor.numpy())

### GPU Acceleration
# Many tensorflow operations are accelerated using teh GPU for computation. Without any annotations, TensorFlow automatically decides whether to use the GPU or CPU for an 
# operation - copying the tensor between the CPU and GPU memory if necessary. Tensors produced by an operation are typically backed by the memory of the device on which the
# operation executed, 

x = tf.random.uniform([3, 3])

print("is there a GPU available: ")
print(tf.config.experimental.list_physical_devices("GPU"))

print("Is the Tensor on GPU #0: "), 
print(x.device.endswith('GPU:0'))

### Device Names
# The Tensor.device property provides a fully qualified string name of the device hosting the contents of the tensor. This name encodes many details, such as an identifer
# of the network address of the host on which this program is executing and the device within that host. This is required for distributed execution of a Tensorflow program. 
# The string ends with GPU:<N> if the tensor is placed on the Nth GPU on the host.

### Explicit Device Placement
# In Tensorflow, placement refers to how individual operations are assigned (placed on) a device for execution. As mentioned, when there is no explicit guidance provided, Tensorflow 
# automatically decides which device to execute an operation on and copies tensors to that device, if needed. However, Tensorflow operations can be explicitly placed on specific devices
# using the tf.device context manager, for example: 

import time

def time_matmul(x):
    start = time.time()
    for loop in range(10):
        tf.matmul(x, x)

    result = time.time() - start
    print("10 loops: {:0.2f}ms".format(1000*result))

# Force execution on CPU
print("on cpu:")
with tf.device("CPU:0"):
    x = tf.random.uniform([1000, 1000])
    assert x.device.endswith("CPU:0")
    time_matmul(x)

# Force execution on GPU #0 if available
if tf.config.experimental.list_physical_devices("GPU"):
    print("On GPU:")
    with tf.device("GPU:0"):
        x = tf.random.uniform([1000, 1000])
        assert x.device.endswith("GPU:0")
        time_matmul(x)

### Datasets
# This section uses the tf.data.Dataset API to build a pipeline for feeding data to your model. The tf.Data.Dataset API is used to build performanct, complex input pipelines from simple, 
# reusable pieces that will feed your model's training or evaluation loops.

#### Create a Source Dataset
# Create a source dataset using one of the factory functions like Dataset.from_tensors, 
# Dataset.from_tensor_slices, or using objects that read from files like TextLineDataset or TFRecordDataset. See the Tensorflow Dataset guide for more information. 

ds_tensors = tf.data.Dataset.from_tensor_slices([1,2,3,4,5,6])

# Create a CSV file
import tempfile

_, filename = tempfile.mkstemp()

with open(filename, 'w') as f:
    f.write(""" Line 1
    Line 2
    Line 3
    """)

    ds_file = tf.data.TextLineDataset(filename)

### Apply transformations
# Use the transformation fuctions like map, batch, and shuffle to apply transformations to dataset records.

ds_tensors = ds_tensors.map(tf.square).shuffle(2).batch(2)
ds_file = ds_file.batch(2)

### Iterate 
# tf.data.Dataset objects support iteration to loop over records
print('Elements of ds_tensors:')
for x in ds_tensors:
    print(x)

print('\nElements in ds_file:')
for x in ds_file:
    print(x)



