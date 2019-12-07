
# Before getting to cross entropy, let's do a little refresher on entropy, a measurement of how certain an event is. It describes how unpredictable that
# probability distribution is. entropy = 1, truly random, entropy = 0, data is truly uniform and so we can always predicts its value.
#
# so now, cross entropy, is just the average message length, if there are 8 options, we can make a bit string to rep each of these states with 3 bits, 
# because 2^3 == 8
#
# for cross entropy, we do sum of pilog(qi), instead of the normal entropy equation, sumo f pilog(pi). Here, qi, is the predicted probability, and pi
# is the actual probability. 

# cross entropy, also known as log loss, measures the performance of a classification model, whose output is a probability between 0 and 1.
# log loss penalizes both types of errors, but especially those that are both confident and wrong. It is a common loss function for training classifiers.
#
# when the predicted distribution is identical to the actual distribution, the cross-entropy is simply equal to the entropy. When they are not the same, the cross entropy will be greater than the entropy by some number of bits. This extra amount that the cross entropy is greater than the entropy is called
# the relative entropy, aka, the KL Divergence.
#
# Code
#
#def CrossEntropy(yHat, y):
#    if y == 1:
#      return -log(yHat)
#    else:
#      return -log(1 - yHat)
#
# In information theory, the cross entropy between two probability distributions p and q over the same
# underlying set of events measures the average number of bits needed to identify an event drawn from the set, if a coding scheme is used that
# is optimized for an "artificial" probability distribution q, rather than the "true" distribution p. 
