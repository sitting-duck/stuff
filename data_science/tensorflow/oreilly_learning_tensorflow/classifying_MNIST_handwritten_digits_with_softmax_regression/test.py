import tensorflow as tf

from tensorflow.examples.tutorials.mnist import input_data

DATA_DIR = '/tmp/data'
NUM_STEPS = 1000
MINIBATCH_SIZE = 100

# First we copy the dataset onto our local harddrive into /tmp/data
# one_hot refers to if the data will use one_hot encoding. In this case, we will. 
# in MNIST, the labels are 0–9. You can either encode that as an integer, or in one-hot encoding where -
# 5 = 0000010000
# 2 = 0010000000
# The index of the thing we want is the 'hot' one.
# etc.
data = input_data.read_data_sets(DATA_DIR, one_hot=True)

# Inserts a placeholder for a tensor that will be always fed.
# Important: This tensor will produce an error if evaluated.
x = tf.placeholder(tf.float32, [None, 784])
W = tf.Variable(tf.zeros([784, 10]))

print x 

y_true = tf.placeholder(tf.float32, [None, 10])
y_pred = tf.matmul(x, W)

