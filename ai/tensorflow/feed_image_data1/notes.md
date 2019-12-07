Before using tensorflow the author used Torch7 or caffe. The author turned to tensorflow because he believed tensorflow will have better support for mobile because of Android. 

Torch7 is from facebook. Torch7 is much easier for the dev. Torch7 uses Lua. Torch7 is a very fast framework, the drawback is that torch7 achieves faster training and inference speed at the cosr of requiring more memory. 

Torch7 io api is so user friendly, the only thing that you need to load an image to it is to call an imread function with the path/to/jpg.jpg

For tensorflow, the basic titorial didn't tell you how to load your own data to form an efficent input data. In the official basic totorials, they provided the way to decode the mnist dataset and cifar10 dataset, both were binary format, but our own image usually is .jpg or .png format. This is why the author wrote this post, there seems not good support for this on tensorflow documentation.

numpy is written in c under the hood, so the speed should be pretty good. 

The author highly recommend reading this tutorial. 
https://www.oreilly.com/learning/hello-tensorflow

The author says the goal is to feed image data to tensorflow and build a simple convolutional neural network. 

The author has hosted a demo here: 
https://github.com/yeephycho/tensorflow_input_image_by_tfrecord

First thing is to write a python script to turn all the images and associated label from a folder, (folder is named after the label) into a tfRecord file, then feed the tfRecord into the network
