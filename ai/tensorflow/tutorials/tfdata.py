import tensorflow as tf
import numpy as np
import pathlib
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

np.set_printoptions(precision=4)

### Consuming NumPy Arrays

# if all your data fits in memory, the simplest way to create a Dataset from them is to convert them to tf.Tensor objects and use Dataset.from_tensor_slices()

train, test = tf.keras.datasets.fashion_mnist.load_data()

images, labels = train
images = images/255

dataset = tf.data.Dataset.from_tensor_slices((images, labels))
dataset

## <TensorSliceDataset shapes: ((28, 28), ()), types: (tf.float64, tf.uint8)>

### Consuming Python generators
# Another common data source that can easily be ingested as a tf.data.Dataset is the python generator.

# caution: while this is a convenient approach it has limited portability and scaliability. It must run in the same python process that created the generator and is still subject to the
# Python GIL

def count(stop):
    i = 0
    while i < stop:
        yield i
        i += 1
        
for n in count(5):
    print(n)
    
# 0 
# 1
# 2
# 3
# 4

# The Dataset.from_generator constructor converts the python generator to a fully functional tf.data.Dataset

# the ctor takes a callable an an input, not an iterator. This allows it to restart the generator when it reaches the end. It takes an optional args, argument, which is passed
# as the callables arguments

# The output_types argument is required becuase tf.data builds a tf.Graph internall, and graph edges require a tf.dtype

ds_counter = tf.data.Dataset.from_generator(count, args=[25], output_types=tf.int32, output_shapes=(), )

for count_batch in ds_counter.repeat().batch(10).take(10):
    print(count_batch.numpy())


# the output_shapes argument is not required but is highly recommended as many tf operations do not support tensors with an unknown rank. If the length of a particular axis
# is unknown or variable, set it as None in the output_shapes

# it's also important to not that the output_shapes and output_types follow the same nesting rules as other dataset methods.

# Here is an example generator that demonstrates botha spects, it returns tuples of arrays, where the second array is a vector with unknown length.

def gen_series():
    i = 0
    while True:
        size = np.random.randint(0, 10)
        yield i, np.random.normal(size=(size,))
        i += 1

for i, series in gen_series():
    print(i, ":", str(series))
    if i > 5:
        break

ds_series = tf.data.Dataset.from_generator(
    gen_series, 
    output_types=(tf.int32, tf.float32), 
    output_shapes=((), (None,)))

ds_series

# Now it can be used like a regular tf.data.DAtaset. Note that when batching a dataset with a variable shape, you need to use Dataset.padded_batch

ds_series_batch = ds_series.shuffle(20).padded_batch(10, padded_shapes=([], [None]))

ids, sequence_batch = next(iter(ds_series_batch))
print(ids.numpy())
print()
print(sequence_batch.numpy())

# In 2.2 you will be able to do it like this, wo the padded_shape args
#ds_series_batch = ds_series.shuffle(20).padded_batch(10)

# For a more realistic exaple, try wrapping preprocessing.image.ImageGenerator as a tf.data.Dataset

# first download the data
flowers = tf.keras.utils.get_file(
    'flower_photos',
    'https://storage.googleapis.com/download.tensorflow.org/example_images/flower_photos.tgz',
    untar=True)

# Create the image.ImageDataGenerator
img_gen = tf.keras.preprocessing.image.ImageDataGenerator(rescale=1./255, rotation_range=20)
images, labels = next(img_gen.flow_from_directory(flowers))

print(images.dtype, images.shape)
print(labels.dtype, labels.shape)

ds = tf.data.Dataset.from_generator(
        img_gen.flow_from_directory, args=[flowers],
        output_types=(tf.float32, tf.float32),
        output_shapes=([32, 256, 256, 3], [32, 5])
        )
ds

# <FlatMapDataset shapes: ((32, 256, 256, 3), (32, 5)), types: (tf.float32, tf.float32)>

### Consuming TFRecord Data
# The tf.data API supports a veriety of file formats so that you can process large dtasets that do not fit in memory. 
# For example, the TFRecord file format is a simple record-oriented binary format that many TF applications us for trianing data. 
# The tf.data.TFRecordDataset class enables you to stream over the contents of one or more TFRecord files as part of an input pipeline.

# Here is an example using the test file from the French Street Name Signs (FSNS)

# Create a dataset that reads all of the examples from two files
fsns_test_file = tf.keras.utils.get_file("fsns.tfrec", "https://storage.googleapis.com/download.tensorflow.org/data/fsns-20160927/testdata/fsns-00000-of-00001")

# the filenames argument to the TFRecordDataset initializer can either be a string, a list of strings, or a tf.Tensor of strings. Therefore if you have two sets of files for training and 
# validations purposes, you can create a factory method that produces the dataset, taking filenames as an input argument. 

dataset = tf.data.TFRecordDataset(filenames = [fsns_test_file])
dataset

# <TFRecordDatasetV2 shapes: (), types: tf.string>

# Many TF projects use serialized tf.train.Example records in their TFRecord files. These need to be decoded before they can be inspected. 

raw_example = next(iter(dataset))
parsed = tf.train.Example.FromString(raw_example.numpy())

parsed.features.feature['image/text']

#bytes_list {
#  value: "Rue Perreyon"
#}

### Consuming Sets of Files 
# There are many datasets distributed as a set of files, where each file is an example.

flowers_root = tf.keras.utils.get_file(
        'flower_photos', 
        'https://storage.googleapis.com/download.tensorflow.org/example_images/flower_photos.tgz',
        untar=True)
flowers_root = pathlib.Path(flowers_root)

# the root diretory contains a directory for each class

for item in flowers_root.glob("*"):
    print(item.name)

#sunflowers
#daisy
#LICENSE.txt
#roses
#tulips
#dandelion

# the files in each class directory are examples: 
list_ds = tf.data.Dataset.list_files(str(flowers_root/'*/*'))

for f in list_ds.take(5):
    print(f.numpy())

#b'/home/kbuilder/.keras/datasets/flower_photos/roses/2980099495_cf272e90ca_m.jpg'
#b'/home/kbuilder/.keras/datasets/flower_photos/sunflowers/14678298676_6db8831ee6_m.jpg'
#b'/home/kbuilder/.keras/datasets/flower_photos/tulips/485266837_671def8627.jpg'
#b'/home/kbuilder/.keras/datasets/flower_photos/daisy/7377004908_5bc0cde347_n.jpg'
#b'/home/kbuilder/.keras/datasets/flower_photos/dandelion/9726260379_4e8ee66875_m.jpg'


# REad the data using the tf.io.read_file function and extract the label from the path, return (image, label) pairs,

def process_path(file_path):
    label = tf.strings.split(file_path, '/')[-2]
    return tf.io.read_file(file_path), label

labeled_ds = list_ds.map(process_path)

for image_raw, label_text in labeled_ds.take(1):
    print(repr(image_raw.numpy()[:100]))
    print()
    print(label_text.numpy())

### Batching Dataset Elements

# Simple Batching
# the simplest form of batching stacks n consecutive elements of a dataset into a single element. The Dataset.batch() transformation does exactly this, with the same constraints as the
# tf.stack() operator, applied to each component of the elements, ie. for each component i, all elements must have a tensor of the exact same shape.

inc_dataset = tf.data.Dataset.range(100)
dec_dataset = tf.data.Dataset.range(0, -100, -1)
dataset = tf.data.Dataset.zip((inc_dataset, dec_dataset))
batched_dataset = dataset.batch(4)

for batch in batched_dataset.take(4):
    print(arr.numpy() for arr in batch)

# [array([0, 1, 2, 3]), array([ 0, -1, -2, -3])]
# [array([4, 5, 6, 7]), array([-4, -5, -6, -7])]
# [#array([ 8,  9, 10, 11]), array([ -8,  -9, -10, -11])]
# [array([12, 13, 14, 15]), array([-12, -13, -14, -15])]

# while tf.data tries to propogate shape information, the default settings of Dataset.batch result in an unknown batch size because the last batch may not be full. 
# Notye the Nones in the shape.

batched_dataset

# <BatchDataset shapes: ((None,), (None,)), types: (tf.int64, tf.int64)>

# Use the drop_remainder argument to ignore that last batch, and get full shape propagation.

batched_dataset = dataset.batch(7, drop_remainder=True)
batched_dataset

# Use the drop_remainder argument to ignore that last batch, and get full shape propagation:

batched_dataset = dataset.batch(7, drop_remainder=True)
batched_dataset

# <BatchDataset shapes: ((7,), (7,)), types: (tf.int64, tf.int64)>

### Batching tensors with padding

# The above recipe works for tensors that all have the same size. However, many models (eg sequence models) work with input data that can have varying size (eg. sequences of different lengths) To handle this case, the Dataset.padded_batch transformation enables you to batch tensors of different shape by specifying one or more dimensions in which they may be padded. 

dataset = tf.data.Dataset.range(100)

#print("Range 100 dataset: ")
#for element in dataset:
#    print(element)

dataset = dataset.map(lambda x: tf.fill([tf.cast(x, tf.int32)], x)) # fill the array element with input x, x number of times

# We can see when we print, x=1, the array is 1 long and full of 1s, x = 2 the array is 2 long and full of 2s and so on.
#print("dataset after call to map: ")
#for element in dataset:
#    print(element)

dataset= dataset.padded_batch(4, padded_shapes=(None, ))

for batch in dataset.take(2):
    print(batch.numpy())
    print()

# [[0 0 0]
# [1 0 0]
# [2 2 0]
# [3 3 3]]
#
#[[4 4 4 4 0 0 0]
# [5 5 5 5 5 0 0]
# [6 6 6 6 6 6 0]
# [7 7 7 7 7 7 7]]

# The dataset.padded_batch transofmarmation allows you to set different padding for each dimension of each component, and it may be variable length (signified by None in the example above)
# or constant length. It is also possible to override the padding value, which defaults to 0.

### Training Workflows

## Processing multiple epochs

# The tf.data API offers two main ways to process multiple epochs of the same data. 
# The simplest way to iterate over a dataset in multiple epochs is to use the Dataset.repeat()
# transformation. First, create a dataset of titanic data: 

titanic_file = tf.keras.utils.get_file("train.csv", "https://storage.googleapis.com/tf-datasets/titanic/train.csv")

### Preprocessing Data
# The Dataset.map(f) transformation produces a new dataset by appluting a given funcction f to each element of the input dataset. It is based on the map() function that is commonly applied
# to lists (and other structures) in functional programming languages. The function f takes the tf.Tensor objects that represent a single element in the input, and returns the 
# tf.Tensor objects that will represent a single element in the new dataset. Its implementation uses standard Tensorflow operations to transform one element into another. 

# This section covers common examples of how to use Dataset.map()

### Decoding image data and resizing it

# when training a neural network on real world image data, it is often necessary to convert images of different sizes to a common size, so that they may be batched into a fixed size. 

# Rebuild the flower filenames dataset: 

list_ds = tf.data.Dataset.list_files(str(flowers_root/'*/*'))

# Write a function that manipulates the dataset elements
# Reads an image form a file, decodes it into a dense tensor, and resizes it into a fixed shape

def parse_image(filename):
    parts = tf.strings.split(filename, '/')
    label = parts[-2]
    
    image = tf.io.read_file(filename)
    image = tf.image.decode_jpeg(image)
    image = tf.image.convert_image_dtype(image, tf.float32)
    image = tf.image.resize(image, [128, 128])
    return image, label

# Test that it works

file_path = next(iter(list_ds))
image, label = parse_image(file_path)

#def show(image, label):
#    plt.figure()
#    plt.imshow(image)
#    plt.title(label.numpy().decode('utf-8'))
#    plt.axis('off')
#
#show(image, label)

# Map it over the dataset

images_ds = list_ds.map(parse_image)

#for image, label in images_ds.take(2):
#    show(image, label)

# Applying arbitrary Python logic
# for performance reasons, use Tensorflow operations for preprocessing your data whenever possible. 
# However, it is sometimes usefult to call external Python libraries when parsing your input data. You can 
# use the tf.py_function() operation in a Dataset.map() transformation

# For example if you want to apply a random rotation, the tf.image module only has the tf.image.rot() which is not very usefult for image augmentation.

# To demo tf.py_function, try using the scipy.ndimge.rotate function instead:

import scipy.ndimage as ndimage

def random_rotate_image(image):
    image = ndimage.rotate(image, np.random.uniform(-30, 30), reshape=False)
    return image

image, lanel = next(iter(images_ds))
image = random_rotate_image(image)
#show(image, label)

# To use this function with Dataset.map the same caveats apply as with Dataset.from_generator, you need to describe the return shapes and types when you apply the function:

def tf_random_rotate_image(image, label):
    im_shape = image.shape
    [image,] = tf.py_function(random_rotate_image, [image], [tf.float32])
    image.set_shape(im_shape)
    return image, label

image, label = next(iter(images_ds))
image = random_rotate_image(image)
#show(image, label)


rot_ds = images_ds.map(tf_random_rotate_image)

# Can't show anything over ssh
#for image, label in rot_ds.take(2)
    #show(image, label)

### Parsing tf.Example protocol buffer messages
# Many input pipelines extract tf.train.Example protocol buffer messages
# from a TFRecord format. Each tf.train.Example record contains one or more
# features and the input pipeline typically converts these features into 
# tensors.

fsns_test_file = tf.keras.utils.get_file("fsns.tfrec", "https://storage.googleapis.com/download.tensorflow.org/data/fsns-20160927/testdata/fsns-00000-of-00001")
dataset = tf.data.TFRecordDataset(filenames = [fsns_test_file])
dataset

# <TFRecordDatasetV2 shapes: (), types: tf.string>

# You can work with tf.train.Example protos outside of a tf.data.Dataset to 
# to understand the data: 

raw_example = next(iter(dataset))
parsed = tf.train.Example.FromString(raw_example.numpy())

feature = parsed.features.feature
raw_img = feature['image/encoded'].bytes_list.value[0]
img = tf.image.decode_png(raw_img)
#plt.imshow(img)
#plt.axis('off')
#_ = plt.title(feature["image/text"].bytes_list.value[0])

raw_example = next(iter(dataset))

def tf_parse(eg):
    example = tf.io.parse_example(
            eg[tf.newaxis], {
                'image/encoded': tf.io.FixedLenFeature(shape=(), dtype=tf.string), 
                'image/text': tf.io.FixedLenFeature(shape=(), dtype=tf.string)
                })
    return example['image/encoded'][0], example['image/text'][0]

img, txt = tf_parse(raw_example)
print(txt.numpy())
print(repr(img.numpy()[:20]), "...")

### Iterator Checkpointing
# Tensorflow supports taking checkpoints so that when your training process
# restarts it can restore the latest checkpoint to recover most of its 
# progress. In addition to checkpointing the model variables, you can also
# checkpoint the progress of the dataset iterator. This could be useful
# if you have a large dataset and don't want to start the dataset from
# from the beginning on each restart. Note however that iterator checkpoints
# may be large, since transformations such as shuffle and prefetch require
# buffering elements within the iterator

# To include your iterator in a checkpoint, pass the iterator to the
# tf.train.Checkpoint constructor
range_ds = tf.data.Dataset.range(20)

iterator = iter(range_ds)
ckpt = tf.train.Checkpoint(step=tf.Variable(0), iterator=iterator)
manager = tf.train.CheckpointManager(ckpt, '/tmp/my_ckpt', max_to_keep=3)

print([next(iterator).numpy() for _ in range(5)])

save_path = manager.save()

print([next(iterator).numpy() for _ in range(5)])

ckpt.restore(manager.latest_checkpoint)

print([next(iterator).numpy() for _ in range(5)])

### Using High Level APIs
# The tf.keras API simplifies many aspects of creating and executing 
# machine learning models. Its .fit() and .evaluate() and .predict()
# APIs support datasets as inputs. Here is a quick dataset and model
# setup. 

train, test = tf.keras.datasets.fashion_mnist.load_data()

images, labels = train
images = images/255.0
labels = labels.astype(np.int32)

fmnist_train_ds = tf.data.Dataset.from_tensor_slices((images, labels))
fmnist_train_ds = fmnist_train_ds.shuffle(5000).batch(32)

model = tf.keras.Sequential([
    tf.keras.layers.Flatten(), 
    tf.keras.layers.Dense(10)
    ])

model.compile(optimizer='adam',
        loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
        metrics=['accuracy'])

# Passing a dataset of (feature, label) pairs is all that's needed for 
# Model.fit and Model.evaluate

model.fit(fmnist_train_ds, epochs=2)

# If you pass an infinite dataset, for example by calling Dataset.repeat()
# you just need to also pass the steps_per_epoch argument




