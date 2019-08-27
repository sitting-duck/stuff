import tensorflow as tf

# Here is the function signature for tf.reduce_mean
# tf.math.reduce_mean(
#    input_tensor,
#    axis=None,
#    keepdims=None,
#    name=None,
#    reduction_indices=None,
#    keep_dims=None
#)
# For me axis translates to "where do you add the additional numbers to increase the dimension." 

# we pretty much cannot do or execute anything without creating a session
sess = tf.Session()

# let's make a tensor, and fill it with some values
mytensor = tf.constant([[100, 110], [10, 20], [1000, 1100]])

print "let's make a tensor!"
print(sess.run(mytensor))

print "If I call reduce_mean on my tensor I just made, I get this:"
print "with_no_dimension = tf.reduce_mean(mytensor)"
with_no_dimension = tf.reduce_mean(mytensor)
print(sess.run(with_no_dimension))

print  "That's because with no axis or any other arguments passed in the default behavior is just to"
print "avarage all the elements of the tensor and return that average value."

average = (100 + 110 + 10 + 20 + 1000 + 1100)/6 
print "Let's prove it."
print "average = (100 + 110 + 10 + 20 + 1000 + 1100)/6"
print "average = " + str(average)

print "with_dimension_0 = tf.reduce_mean(mytensor, 0)"
with_dimension_0 = tf.reduce_mean(mytensor, 0)
print "if we add 0 as the axis argument, we can see that it is averaging every column"
print(sess.run(with_dimension_0))

print "with_dimension_0 = tf.reduce_mean(mytensor, 1)"
with_dimension_1 = tf.reduce_mean(mytensor, 1)
print "if we instead add 1 as the axis argument, we can see that is averaging every row"
print(sess.run(with_dimension_1))

