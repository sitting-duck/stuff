import os
import cv2

def get_ssim(image1, image2):
    
    print image1
    print image2
  
    print os.path.exists(os.path.dirname(os.path.realpath(__file__)))
    print os.path.exists(os.path.dirname(os.path.realpath(__file__)) + "/sequenced_footage/")
    print os.path.isfile(image1)
    print os.path.isfile(image2)

    if not os.path.isfile(image1) or not os.path.isfile(image2):
        raise("input image does not exist")
        return

    # load the two input images
    imageA = cv2.imread(image1)
    imageB = cv2.imread(image2)
    cv2.imshow("A", imageA)
    cv2.imshow("B", imageB)

    # convert the images to grayscale
    grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
    grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)

    # compute the Structural Similarity Index (SSIM) between the two
    # images, ensuring that the difference image is returned
    (score, diff) = compare_ssim(grayA, grayB, full=True)

    #diff is an array of floats [0,1], we convert to 8bit uint [0-255] so we can do imageproc
    diff = (diff * 255).astype("uint8")
    print("SSI<: {}".format(score))
    return score

def main():
   
    videoFolder = "sequenced_footage/" # the folder with all the frames saved as images in it
    pwd = os.path.dirname(os.path.realpath(__file__))

    for _, dirs, _ in os.walk(videoFolder):
        for dir in dirs:
            print dir
            for _, _, files in os.walk(videoFolder + dir):
                pass
            #    for file in files:
            #        print "\t" + file
            files = sorted(files)

            # we make a loop for looping through these files using an index
            # using i and i+1 to fetch two adjacent files is really convenient for us in this situation
            for i in range(0, len(files)):
                #print i
                if (i+1) < len(files):
                    #print str(videoFolder+files[i]) + " " + str(videoFolder+files[i+1])
                    print get_ssim(pwd+"/"+videoFolder+"/"+dir+"/"+files[i], pwd+"/"+videoFolder+"/"+dir+"/"+files[i+1]) 

if __name__ == "__main__":
    main()


