# this script is just for inspecting an onnx file and printing out some basic things about it, such as its input names and output names.

import onnxruntime as ort
import numpy as np

from onnxruntime.datasets import get_example

#X = np.array([1,2,3,4,5])
#ortvalue = ort.OrtValue.ortvalue_from_numpy(X, 'cuda', 0)


sess = ort.InferenceSession("example.onnx")

input_name = sess.get_inputs()[0].name
print("input_name: " + input_name)

input_shape = sess.get_inputs()[0].shape
print("input_shape: " + str(input_shape))

input_type = sess.get_inputs()[0].type
print("input type: " + str(input_type))


output_name = sess.get_outputs()[0].name
print("output name: " + output_name)

output_shape = sess.get_outputs()[0].shape
print("output_shape: " + str(output_shape))

output_type = sess.get_outputs()[0].type
print("output_type: " + str(output_type))

# lets compute its outputs 
#import numpy.random
#x = numpy.random.random((3,4,5))
#x = x.astype(numpy.float32)
#res = sess.run([output_name], {input_name: x})
#print(res)
