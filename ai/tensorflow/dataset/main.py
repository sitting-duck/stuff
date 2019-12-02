
import tensorflow as tf
import tensorlayer as tl

import file_tools as ft

paths = ["images"]
valid_extensions = [".tiff", ".tif", ".png", ".jpg"]
filenames = ft.files(paths, valid_extensions) 
dataset = tf.data.Dataset.from_tensor_slices((filenames))
