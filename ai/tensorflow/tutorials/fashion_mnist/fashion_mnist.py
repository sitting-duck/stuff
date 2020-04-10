import tensorflow as tf
from tensorflow import keras

import matplotlib
matplotlib.use('Agg') # so I can see pyplot over ssh

import numpy as np
import matplotlib.pyplot as plt

print(tf.__version__)


def plot_image(i, predictions_array, true_label, img):
  predictions_array, true_label, img = predictions_array, true_label[i], img[i]
  plt.grid(False)
  plt.xticks([])
  plt.yticks([])

  plt.imshow(img, cmap=plt.cm.binary)

  predicted_label = np.argmax(predictions_array)
  if predicted_label == true_label:
    color = 'blue'
  else:
    color = 'red'

  plt.xlabel("{} {:2.0f}% ({})".format(class_names[predicted_label],
                                100*np.max(predictions_array),
                                class_names[true_label]),
                                color=color)

def plot_value_array(i, predictions_array, true_label):
  predictions_array, true_label = predictions_array, true_label[i]
  plt.grid(False)
  plt.xticks(range(10))
  plt.yticks([])
  thisplot = plt.bar(range(10), predictions_array, color="#777777")
  plt.ylim([0, 1])
  predicted_label = np.argmax(predictions_array)

  thisplot[predicted_label].set_color('red')
  thisplot[true_label].set_color('blue')

def main():
    # fashion mnist

    # slightly more challenging than mnist, 
    # a hello world type of dataset that can be used to verify that an algorithm is working as expected

    # 60K images are used to train and 10L images for test

    fashion_mnist = keras.datasets.fashion_mnist

    (train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

    # images are 28x28 Numpy arrays, pixel values from 0 to 255. 
    # The labels are an array of integers, ranging from 0 to 9. These correspond to the class of clothing the image represents:

    # 0 - top
    # 1 - trouser
    # 2 - pullover
    # 3 - dress
    # 4 - coat
    # 5 - sandal
    # 6 - shirt
    # 7 - sneaker
    # 8 - bag
    # 9 - ankle boot

    class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
                   'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

    ### Preprocess the data
    # the data must be preprocessed before training the network. If you inspect the first image in the training set, you will
    # see that the pixel values fall in the range of 0 to 255

    # scale these values to a rande of 0 to 1 before feeding them to the neural network model. To do so, 
    # divide the values by 255. It's important that the training set and the testing set be preprocessed in the same way. 

    train_images = train_images / 255.0
    test_images = test_images / 255.0

    # to verify that the data is in the correct format and that you're ready to build and train the network, let's 
    # display the first 25 images from the training set and display the class name below each image
    # Note: this seems not display the plot over ssh even when I use ssh -X or ssh -Y
    plt.figure(figsize=(10,10))
    for i in range(25):
        plt.subplot(5,5,i+1)
        plt.xticks([])
        plt.yticks([])
        plt.grid(False)
        plt.imshow(train_images[i], cmap=plt.cm.binary)
        plt.xlabel(class_names[train_labels[i]])
    plt.show()

    ### Build the Model

    # building the neural network requires configuring the layers of the model, then compiling the model.

    # Set up the layers

    # the basic building block of a neural network is the layer. Layers extract representations from the data fed into them. Hopefully, these representations are meaningful for the problem at hand. 

    # Most of deep learning consists of chaining together simple layers. 
    # Most layers, such ass tf.keras.layers.Dense, have parameters that are learned during training. 

    model = keras.Sequential([
        keras.layers.Flatten(input_shape=(28, 28)),
        keras.layers.Dense(128, activation='relu'),
        keras.layers.Dense(10)
        ])

    # The first layer in this network, tf.keras.layers.Flatten, transforms the format of the images form a two dimensional array (of 28x28 pixels) to a 1 dimensional array of 28x28 = 784 pixels. 
    # Think of this layer as unstacking rows of pixels in the image and lining them up. This layer has no parameters to learn; it only reformats the data. 

    # After the pixels are flattened, the network consists of a sequence of two tf.keras.layers.Dense layers. These are densely connected, or fully connected, neural layers. The first 
    # Dense layer has 128 nodes (or neurons).

    # The second (and last) layer returns a logits array with a length of 10. Each node contains a score that indicates the current image belongs to 1 of the 10 classes. 

    ### Compile the model

    # Before the model is ready for training, it needs a few more settings. These are added during the model's compile step:
    # loss function: this measures how accurate the model is during training. You want to minimize this function to "steer" the model in the right direction. 
    # optimizer: this is how the model is updated based on the data it sees and its loss function. 
    # metrics: used to monitor the training and testing steps. The following example uses accuracy, the franction of the images that are correctly classified. 

    model.compile(optimizer='adam',
            loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
            metrics=['accuracy'])

    ### Train the model
    # Training the neural network model requires the following steps. 
    # 1. Feed the training data to the model. In this example, the training data is in the train_images and train_labels arrays.
    # 2. the model lears to associate images and labels. 
    # 3. You ask the model to make predictions about a test set - in this example, the test_images array.
    # 4. Verify that the predictions match the labels from the test_labels array.

    ### Feed the model

    # to start training, call the model.fit method -- so called because it "fits" the model to the training data. 

    model.fit(train_images, train_labels, epochs=10)


    # as the model trains, the loss and accuracty metrics are displayed. This model reaches an accuracy of about 91% on the training data. 

    ### Evaluate Accuracy

    # next compare how the model performs on the test dataset: 
    test_loss, test_acc = model.evaluate(test_images, test_labels, verbose=2)

    print('\nTest Accuracy: ', test_acc)

    # It turns out that the accuracy on the test dataset is a little less than the accuracy on the training dataset. This gap between training
    # and accuracy represents overfitting. Overfitting happens when a machine learning model performs worse on new, previously unseen inputs than it does on the training data. 
    # An overfitted model "memorizes" the noise and details in the training dataset to a point where it negatively impacts the performance of the model on the new data. 

    ### Make predictions

    # with the model trained, you can use it to make predictions about some images. The model's linear outputs, logits. Attach a softmaz layer to convert the logits to probabilities, 
    # which are easier to interpret. 

    probability_model = tf.keras.Sequential([model, tf.keras.layers.Softmax()])
    predictions = probability_model.predict(test_images)

    # Here, the model has predicted the label for each image in the testing set. Let's take a look at the firt prediction. 

    print("predictions[0] is a 10 long array, with each slot containing the probability that input is a member of that class")
    print(predictions[0])

    print("so, if we take the max from those, we will get the class this net proposes is most likely. ")
    print(np.argmax(predictions[0]))

    # so the model is most confident that this image is an ankle boot, or class_names[9]. Examining the test label shows that this classification is correct. 

if __name__ == '__main__':
    main()
