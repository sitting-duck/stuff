
import tensorflow as tf
import tensorlayer as tl

import file_tools as ft

# The purpose of this code is to test and to demo the usage of the functions in file_tools.py

# So let's create a Tensorflow dataset with some folders of example images I have found on a data collection mission.

paths = ["images/png", "images/webp"]
valid_extensions = [".tiff", ".tif", ".png", ".jpg", ".jpeg", ".webp"]
filenames = ft.files(paths, valid_extensions) 
dataset = tf.data.Dataset.from_tensor_slices((filenames))

print("We've made our first Tensorflow dataset!")

# Let's do it again and this time we shuffle the files before creating a Tensorflow dataset. Shuffling the files can help prevent biases due to the order files are given during training.

paths = ["images/jpg", "images/jpeg"]
valid_extensions = [".tiff", ".tif", ".png", ".jpg", ".jpeg", ".webp"]
filesnames = ft.files(paths, valid_extensions)
filesnames = ft.files_random(paths, valid_extensions)
