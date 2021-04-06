import onnxruntime as ort
import numpy as np

sess = ort.InferenceSession("net.onnx")

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

print("device: " + ort.get_device())


