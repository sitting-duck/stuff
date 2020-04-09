import tensorflow as tf

mnist = tf.keras.datasets.mnist

(x_train, y_train), (x_test, y_test) = mnist.load_data()

x_train, x_test = x_train / 255.0, x_test / 255.0

model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape=(28, 28)),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(10)
    ])

# model returns a vector of logits or log-odds scores, one for each class
predictions = model(x_train[:1]).numpy()
predictions

# softmax function converts these logits to probabilities for each class
tf.nn.softmax(predictions).numpy()

loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)

loss_fn(y_train[:1], predictions).numpy()

model.compile(optimizer='adam',
        loss=loss_fn,
        metrics=['accuracy'])

# the Model.fit method adjusts the model parameters to minimize the loss
model.fit(x_train, y_train, epochs=5)

# The Model.evaluate method checks the models performance, usually on a 'validation set'
model.evaluate(x_test, y_test, verbose=2)

