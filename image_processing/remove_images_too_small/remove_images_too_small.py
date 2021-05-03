import os
from PIL import Image

img_dir = r"/path/to/my/dataset"


for filename in os.listdir(img_dir):
   filepath = os.path.join(img_dir, filename)
   _, file_extension = os.path.splitext(filename)


   if file_extension == ".1" or file_extension == ".2" or file_extension == ".3" or file_extension == ".4" or file_extension == ".5" or file_extension == ".6" or file_extension == ".7" or file_extension == ".8" or file_extension == ".9":
      os.remove(filepath)
      print("removed " + filepath)

   print(file_extension)
   if file_extension == ".jpg" or file_extension == ".jpeg" or file_extension == ".png":
        print(filename)
        with Image.open(filepath) as im:
            x, y = im.size
            print(" x: " + str(x) + " y: " + str(y))
        if x < 768 or y < 768:
            os.remove(filepath)
            print("removed " + filepath)


