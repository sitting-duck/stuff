
This script is for uploading just massive amounts of files to github using git lfs. 

Because we're using git lfs the files can be large files. 

such as *.lib, *.dll. 

This script has been tested on Windows. I will probably write another one for Mac that works with *.dylib

It uses find to list all the files in the directory in question, and then passes these filename strings one by one to a function add_file_and_push_to_github.

This function adds the file to the git index, 

makes a commit "add ${filname}"

pulls the latest history from the branch to avoid conflicts, 

pushes the new commit to the branch.

The result here is that the files are added and pushed to the repo one by one. 

I had to make this because adding too many large files at a time seemed to make the push to branch always hang up and I didn't have a reliable way to figure out exactly what size is the proper size and then only pushing that amount at a time, 

the easier thing to do is to just script each file being added and pushed one by one, since I know a single file itself isn't going to be large enough to make the remote hang up. 

This prevented me from having to watch a large push (which is time consuming) wondering if it would fail, and having to do this over and over until finally I had pushed all the files I need to the repo.

