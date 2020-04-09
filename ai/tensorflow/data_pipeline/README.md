# tf.data: Build TensorFlow input pipelines

The tf.data API introduces a tf.data.Dataset abstraction that represents a sequence of elements, in which each element consists of one or more components. For example, in an image pipeline, an element might be a single training example, with a pair of tensor components representing the image and its label.

The dataset is the foundation of all of this. Treat it with respect.

TFRecord is a formalized data structure, but it appears the simple and easy way to compose a dataaset is using ``from_tensors()`` or ``from_tensor_slices()``

You can ``transform`` your dataset by chaining method calls on the ``tf.data.Dataset`` object. You can apply per-element transformations such as ``Dataset.map()`` and multi-element transformations such as ``Dataset.batch()``

### Dataset Structure

A dataset contains elements that each have the same (nested) structure and the individual components of the structure can be of any type representable by ``tf.TypeSpec`` including ``Tensor`` or ``Dataset`` 

Dataset.element_spec return a nested structure of tf.TypeSpec object, matching the structure of the dataset element. 

Use value_type to see that type of the value represented by the element_spec

```
dataset4.element_spec.value_type
```

# Reading Input Data
## Consuming Numpy Arrays

If all of your input data firs in memory, the simplest way to create a Dataset from them is to convert them to tf.Tensor objects and use Dataset.from_tensor_slices()


