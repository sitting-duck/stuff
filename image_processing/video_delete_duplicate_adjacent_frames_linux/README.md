
**delete_dups.py**: will walk through all the directories in sequenced_footage and delete all adjacent duplicate frames. This will not work if the frames are not named in alpha order. 
It is a safe assumption that two non-adjacent sequenced video frames will never be completely identical because the universe is random enough that from one moment to the next, light particles will never fall again in exactly the same way. 

**frame_sequencer.py**: Will grab all the video files in a directory and for each video file it will make a folder with the same name, and save each video frame as a png into that folder. Each frame png file will be named with the frame number, so the files are technically in alphabetical order.

**image_diff.py**: can be passed two image files. It will print out the ssim score for the two images. The SSIM is a score of similarity. If you comment in the imshow commands at the end of the file, it will display the two files with red rectangles drawn around the areas that are different, as well a black and white difference map, and grayscale image that is a diff of the two input images.

**prereqs.md**: explains what operatings system you can run these scripts on, as well as what dependencies you will need to install before running. 

   
