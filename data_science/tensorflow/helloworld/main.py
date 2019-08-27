import tensorflow as tf
mnist = tf.keras.datasets.mnist

# load_data() Returns 2 tuples. x_train, x_test: uint8 array of RGB image data with shape (num_samples, 3, 32, 32) or (num_samples, 32, 32, 3) based on the image_data_format backend setting of either channels_first or channels_last respectively.
# y_train, y_test: uint8 array of category labels (integers in range 0-9) with shape (num_samples,).

(x_train, y_train), (x_test, y_test) = mnist.load_data()

print(x_train.shape)

# normalize the array values from [0, 255] to [0, 1]
x_train, x_test = x_train/255.0, x_test/255.0

# Dense: a dense nn layer is fully connected. Each output node is connected to each input node
# relu: stabds for rectified linear unit. The func is: y = max(0, x) It is the most common activation function in neural networks especially in CNNs. If you are unsure what activation function to use in your network, relu is usually a good first choice.
# Dropout: 0.2 means we will randomly set 20% of the inputs to the layer to 0. This prevents overfitting.
# softmax typically used for multi classification (as opposed to binary classification)
 
model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape=(28, 28)), # flatten the image from 2D array to 1D array
    tf.keras.layers.Dense(128, activation='relu'), # 
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(10, activation='softmax') 
])

# optimizer: the optimizer listens to the loss function, and then adjusts the weights
# adam: Adaptive Moment Estimation, can use past gradients to predict future gradiants, also utilizes the concept of momentum by adding fractions of a previous gradient gradient to the current one. This optimizer has become pretty widespread and is practically accepted in use for training neural nets
# the compile function configures the model for training
# in practice optimizers can be very very complicated but all you need to know is that their function is to minimize loss.
# sparse_categorical_crossentropy: seems to allow you to input training sets as a 1D array.

model.compile(optimizer='adam',
        loss='sparse_categorical_crossentropy',
        metrics=['accuracy'])

model.fit(x_train, y_train, epochs=5)
model.evaluate(x_test, y_test)


