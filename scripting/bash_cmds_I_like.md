```
# for copyng a buuuuuunch of files, mv will fail out with "too many arguments error" so use this instead
find path/to/folder/ -ctime -1 -type f -name "some*thing" | xarfs -I '{}' mv '{}' ./path/to/folder2

# you can see that the mv command is invoked near the end.
Tested on Linux and/or MacOS
```

