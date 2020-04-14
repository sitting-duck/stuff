import tensorflow as tf

# Note: Do not confuse TFDS (this library) with tf.data (TensorFlow API to 
# build efficient data pipelines). TFDS is a high level wrapper around 
# tf.data.

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import matplotlib.pyplot as plt
import numpy as np
import tensorflow.compat.v2 as tf

import tensorflow_datasets as tfds
tfds.disable_progress_bar()

# Eager Execution 
# Tensorflow Datasets is compatible with both Tensorflow Eager mode 
# and Graph mode. For this colab, we'll run in Eager mode.

tf.enable_v2_behavior()

### List the Available Datasets
# Each dataset is implemented as a tfds.core.DatasetBuilder and you
# can list all available builders with tfds.list_builders()

# tfds.load: A dataset in one line
# tfds.load is a convenience  method that's the simplest way to bulld
# and load a tf.data.Dataset

# tf.data.Dataset is the standard Tensorflow API to build input pipe
# lines. 

# Below we load the MNIST training data. It downloads and prepares
# the data, unless you specify download = False. Note that once data,
# has been prepared, subsequent calls of load will reused the prepared
# data. You can customize where the data is saved/loaded by specifying
# data_dir= (defaults to ~/tensorflow_datasets/)

ds_train = tfds.load(name="mnist", split="train")
assert isinstance(ds_train, tf.data.Dataset)
print(ds_train)

# when loading a dataset, the canonical default version is used. 
# It is however recommended to specify the major version of the 
# dataset to use, and to advertise which version of the dataset
# was used in your results. See the documentation on datasets 
# versioning for more details. 


# eg ds_all = tfds.load("mnist:3.*.*")

### Feature Dictionaries
# all tfds datasets contain feature dictionaries mapping feature names
# to Tensor values. A typical dataset, like MNIST will have 2 keys,
# "image" and "label"

# Below we inspect a single example.

for example in ds_train.take(1):
    image, label = example["image"], example["label"]

# tfds.load is really a thin convenience wrapper around DatasetBuilder
# We can accomplish the same as above directly with the MNIST 
# DatasetBuilder

mnist_builder = tfds.builder("mnist")
mnist_builder.download_and_prepare()
ds_train = mnist_builder.as_dataset(split="train")

### Input Pipleines
# once you have a tf.data.Dataset object, it's simple to define the 
# rest of an input pipeline suitable for model training by using the 
# tf.data API

# Here well repeat the dataset so that we have an infinite stream of
# examples, shuffle, and create batches of 32, 

ds_train = ds_train.repeat().shuffle(1024).batch(32)

ds_train = ds_train.prefetch(tf.data.experimental.AUTOTUNE)
# I guess they use autotune instead of specifying some number

### DatasetInfo
# after generation, the builder contains useful information on the 
# dataset: 

info = mnist_builder.info
print(info)

# DatasetInfo also contains useful information about the features. 

print(info.features)
print(info.features["label"].num_classes)
print(info.features["label"].names)
