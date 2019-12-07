I fork the repo: 

https://github.com/senko/python-video-converter

I build all the stuff, but the automated tests are failing somewhere and I don't understand what the output means. I'm suspicious that it has something to do with ffmpeg. 

I do sudo apt install ffmpeg, and the tests still fail. I decide at this point that I need to actually do a little more research into ffmpeg anyway. 


### How to Encode Raw Video with ffmpeg
https://github.com/stoyanovgeorge/ffmpeg/wiki/Encode-Raw-Video

RAW to Encoded Video Encoding (Y4M)
```
ffmpeg -i inputfile.y4m -c:v libx264 -preset ultrafast outputfile.mp4
```
 - as you can see here the command is also pretty simple. You just need to define the input, output file and the desired codec. The preset part is optional.
