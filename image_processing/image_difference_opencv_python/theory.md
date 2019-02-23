In order to compute the difference between two images we utilize the Structural Similarity Index, first inro by Wang et al in 2004 paper, Image Quality Assessment: From Error Visibility to Structural Similarity

This method is already implemented in the sci-kit image library for image processing.

Another good site with some useful theory on it: 
https://www.learnopencv.com/opencv-threshold-python-cpp/
I like this page because it also shows a c++ implementation side by side with the python implementation

the parent child hierarchy of contours
https://docs.opencv.org/3.1.0/d9/d8b/tutorial_py_contours_hierarchy.html

So what exactly is a contour anyway?
https://docs.opencv.org/3.4.2/d4/d73/tutorial_py_contours_begin.html
A contour is a curve joining all the contiguous points along a boundary that have the same color or intensity value. Contours are most accurate on binary images, so run your image through a binary threshold first for best accuracy.

Copying the script straight from the tutorial I get:
AttributeError: 'tuple' object has no attribute 'copy'
It appears that thresh is a tuple, and it has no function copy().

So what is a tuple exactly? Wow, I really am forgetful, I used to know this I swear :)

a tuple is a sequence of immutable Python objects. Tuples are sequences, just like lists. The differences between tuples and lists are, the tuples cannot be changed unlike lists and tuples use parentheses, whereas lists use square brackets. 
