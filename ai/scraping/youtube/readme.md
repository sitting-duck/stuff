### Links
https://youtube-dl.org/
https://github.com/rg3/youtube-dl/blob/master/README.md

### Installation
To install it right away for all UNIX users (Linux, macOS, etc.), type:
```
sudo curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl
sudo chmod a+rx /usr/local/bin/youtube-dl
```
--ignore-errors - You probably want to use this if you plan on running your script all night

### Gotchas: 
If you lose connectivity and then resume (like if you're switching wifi networks) it will hang in mid-download and cannot be recovered. You'll have to start over or else write a script to check for dups and then resume wherever you were. 
On the bright side, if you resume, it will have the same amount of progress because of the .part file.

extrator simply refers to a website that you want to download videos from.

### Download from a search query
youtube-dl "ytsearch100:how to create android app in app studio"
* only the first 100 videos 

