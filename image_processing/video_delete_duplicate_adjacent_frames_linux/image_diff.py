from skimage.measure import compare_ssim
import argparse
import imutils
import cv2

# construct the argument parser and parse the arguments passed to this script from the command line

ap = argparse.ArgumentParser()
ap.add_argument("-f", "--first", required=True, help="first input image")
ap.add_argument("-s", "--second", required=True, help="second input image")
args = vars(ap.parse_args())

# load the two input images
imageA = cv2.imread(args["first"])
imageB = cv2.imread(args["second"])

# convert the images to grayscale
grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)

# compute the Structural Similarity Index (SSIM) between the two
# images, ensuring that the difference image is returned
(score, diff) = compare_ssim(grayA, grayB, full=True)

#diff is an array of floats [0,1], we convert to 8bit uint [0-255] so we can do imageproc
diff = (diff * 255).astype("uint8")
print("SSI<: {}".format(score))

# the threshold function requires a grayscale image, if a pixel value is greater than the
# threshold, its assigned white, else it is assigned black

#threshold the difference image, followed by finding contours to 
# obtain the regions of the two input images that differ
# diff: the input image being processed 
# 0: the threshold value which is used to classify the pixel values
# 255: maxVal, the value given if pixel value is more than (sometimes less than) the threshold value
# cv2.THRESH_BINARY_INV | cv2.RETR_EXTERNAL: the type of thresholding
# a thresh binary inverted algirothm is really just this: 
#
# if src(x,y) > thresh
#   dst(x,y) = 0 # pixel becomes black
# else
#   dst(x,y) = maxValue # pixel becomes white
#
# RETR_EXTERNAL: is the contour retrieval mode. It means that only extreme outer contours are returned, child contours are not
# CHAIN_APPROX_SIMPLE: stores only the corner points
thresh = cv2.threshold(diff, 0, 255, cv2.THRESH_BINARY_INV | cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

#print "mah thresh:"
#print thresh

cnts = cv2.findContours(thresh[1].copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)



# loop over the contours
for c in cnts:
    # compute the bounding box of the contour and then draw the
    # bounding box on both input images to represent where the 
    # two images differ
    (x, y, w, h) = cv2.boundingRect(c)
    cv2.rectangle(imageA, (x, y), (x + w, y + h), (0, 0, 255), 2)
    cv2.rectangle(imageB, (x, y), (x + w, y + h), (0, 0, 255), 2)

# show the output images
#cv2.imshow("Original", imageA)
#cv2.imshow("Modified", imageB)
#cv2.imshow("Diff", diff)
#cv2.imshow("Thresh", thresh[1])
#cv2.waitKey(0)


