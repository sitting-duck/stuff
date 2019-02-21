from skimage.measure import compare_ssim
import argparse
import imutils
import cv2

# construct the argument parser and parse the arguments passed to this script from the command line

ap = argparse.ArgumentParser()
ap.add_argument("-f", "--first", required=True, help="first input image")

