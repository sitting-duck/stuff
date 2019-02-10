#logit basically means:

#    The raw predictions which come out of the last layer of the neural network.
#    1. This is the very tensor on which you apply the argmax function to get the predicted class.
#    2. This is the very tensor which you feed into the softmax function to get the probabilities for the predicted classes.

