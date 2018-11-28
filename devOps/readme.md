This little snipped is super useful for finding a needle in a haystack: 

  find . -type f -name "*.dylib" -print0 | xargs -0 otool -L {} | grep "5.6.3"
  
  Recursively search the otool output of all the dylibs in a folder for something.
  This saved me so much time I can't even believe it.
  
