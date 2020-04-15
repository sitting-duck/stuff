import tensorflow.compat.v2 as tf
import tensorflow_datasets as tfds

tfds.disable_progress_bar()
tf.enable_v2_behavior()

### Step 1: Create your input pipeline

# shuffle_files: MNIST data is only stored in a single file, but 
# for larger datasets with multiple files on disk, it's good practice
# to shuffle them when training

# as_supervised: returns tuple (img, label) instead of dict
# {'image':img, 'label': label}

(ds_train, ds_test), ds_info = tfds.load(
        'mnist',
        split=['train', 'test'],
        shuffle_files=True,
        as_supervised=True,
        with_info=True,
        )

# Build training pipeline
# apply the following transformations:
# ds.map: TFDS provide the images as tf.uint8, while the model expect
# tf.float32, so normalize images

# ds.cache: as the dataset fit in memory, cache before shuffling for 
# better performance

# ds.suffle: for true randomness, set the shuffle buffer to the full
# dataset size

# note: for bigger datasets which do not fit in memory, a standard 
# value is 1000 if your system allows it

# ds.batch: batch after shuffling to get unique batches at each epoch

# ds.prefetch: good practice to end the pipeline by prefetching for
# performance

def normalize_img(image, label):
    """Normalizes images: uint8 -> float32."""
    return tf.cast(image, tf.float32) / 255., label

ds_train = ds_train.map(
        normalize_img, num_paralell_calls=tf.data.experimental.AUTOTUNE)
ds_train = ds_train.cache()
ds_train = ds_train.shuffle(ds_info.splits['train'].num_examples)
ds_train = ds_train.batch(128)
ds_train = ds_train.prefetch(tf.data.experimental.AUTOTUNE)

### Build Evaluation Pipeline
# testing pipeline is similar to the training pipeline with small 
# differences

# no ds.shuffle() call
# caching is done after batching (as batches can be the same between 
# epoch

ds_test = ds_test.map(
        normalize_img, num_parallel_calls=tf.data.experimental.AUTOTUNE)
ds_test = ds_test.batch(128)
ds_test = ds_test.cache()
ds_test = ds_test.prefetch(tf.data.experimental.AUTOTUNE)


