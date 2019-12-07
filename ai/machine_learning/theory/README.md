### Generative Versus Discriminative Algorithms Notes
# source: https://skymind.ai/wiki/generative-adversarial-network-gan

Discriminative algorithms try to classify input data. They are classifiers.<br/>
y is class label eg. spam, not spam, <br/>
 x is the features of the input eg. the words Nigerian prince, or memo in the email. <br/> 
p(y|x): the probability of y given x. <br/>

Discriminative algorithms map features to labels. They are concerned solely with that correlation. <br/>
A way to think about generative algorithms is that they do the opposite. <br/>

Instead of predicting a label given certain features, they attempt to predict features given a certain label. ie. p(x|y) (notice how x and y are switched around)<br/>

Another way to think of it: 
- Discriminative models learn the boundaries between classes
- Generative models model the distribution of individual classes

### How GANS work
the generator network generates new data instances, 
the discriminator network evaluates them for authenticity. . ie. the disciminator decides whether each instance of data it reviews belongs to the actual training dataset or not. 

### Example
the generator is going to try to generate hand-written numerals like those found in the MNIST dataset. The goal of the discriminator, when shown an instance from the true MNIST dataset, is to recognize them as authentic. 
Meanwhile the generator is creating new images that it passes to the discriminator. It does so in the hopes that they, too, will be deemed authentic, even though they are fake. <br/>

The discriminator network is a standard convolutional network that can categorize the images fed to it, a binomial classifier labeling images as real or fake. 

The generator is an inverse convolutional network. While a standard convolutional classifer takes an images and downsamples it to peoduce a probablility, the generator takes a vector of random noise and upsamples it to an image. The first throws away data through downsampling techniques like maxpooling, the second generates new data. 

Both nets are trying to optimize a different an opposing loss function, in a zero sum game. ie. the actor-critic model. 



 
