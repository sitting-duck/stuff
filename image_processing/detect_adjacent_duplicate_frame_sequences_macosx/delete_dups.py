import os
import cv2
from skimage.measure import compare_ssim

def get_ssim(image1, image2):
	
	if not os.path.isfile(image1):
		print("input image " + image1 + " does not exist")
		raise("input image " + image1 + " does not exist")
		return

	if not os.path.isfile(image2):
		print("input image" + image2 + " does not exist")
		raise("input image" + image2 + " does not exist")
		return

	# load the two input images
	imageA = cv2.imread(image1)
	imageB = cv2.imread(image2)

	# convert the images to grayscale
	grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
	grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)

	# compute the Structural Similarity Index (SSIM) between the two
	# images, ensuring that the difference image is returned
	(score, diff) = compare_ssim(grayA, grayB, full=True)

	#diff is an array of floats [0,1], we convert to 8bit uint [0-255] so we can do imageproc
	diff = (diff * 255).astype("uint8")
	#print("SSI<: {}".format(score))
	return score

def sort_list(list):
	index_list = sorted(range(len(list)), key=list.__getitem__)

	sorted_list = []
	for k in range(0, len(index_list)):
		sorted_list.append(list[index_list[k]])
	return sorted_list

def main():
   
	#videoFolder = "/Volumes/Albert-viddata/video800_new/" # the folder with all the frames saved as images in it
	videoFolder = "./footage/" # the folder with all the frames saved as images in it
		#check that this videoFolder actually exists
	if not os.path.isdir(videoFolder):
		print("video folder " + videoFolder + " does not exist")
		raise("video folder " + videoFolder + " does not exist")

	pwd = os.path.dirname(os.path.realpath(__file__))

	for _, dirs, _ in os.walk(videoFolder):
		for dir in dirs:
			print(dir)

			if not os.path.isdir(videoFolder + dir):
				print("ERROR: " + videoFolder + dir + "is not a folder")

			for _, _, files in os.walk(videoFolder + dir):
				pass

			for file in files:
				print(file)

			files = sort_list(files)
			
			print("num files before: " + str(len(files)))

			#for m in range(0, len(files)):
				#print m
				#print files[m]
			# we make a loop for looping through these files using an index
			# using i and i+1 to fetch two adjacent files is really convenient for us in this situation
			for i in range(0, len(files)):

				#if (i+1) < len(files) - 1:
					#print i
					#print "i: " + str(files[i])
					#print "i+1: " + str(files[i+1])
					#print "comparing " + str(files[i]) + " and " + str(files[i+1])
				if (i+1) < len(files):
					file1 = pwd+"/"+videoFolder+"/"+dir+"/"+files[i]
					file2 = pwd+"/"+videoFolder+"/"+dir+"/"+files[i+1]
					ssim = round(get_ssim(file1, file2), 2) 
					#print "ssim: " + str(ssim)
					if ssim >= 0.99:
						print("same: "+ str(file1) + str(file2))
						os.remove(file2)
									
				for _, _, files in os.walk(videoFolder + dir):
					pass
				files = sort_list(files)

			print("num files after: " + str(len(files))) 

if __name__ == "__main__":
	main()


