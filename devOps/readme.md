This little snipped is super useful for finding a needle in a haystack: 

  find . -type f -name "*.dylib" -print0 | xargs -0 otool -L {} | grep "5.6.3"
  
  Recursively search the otool output of all the dylibs in a folder for something.
  This saved me so much time I can't even believe it.
  
<hr>

For removing all the bloat from a Qt deploy environment

### DESTROY ALL DEBUG FILE BLOAT DRAGGED IN BY MACDEPLOYQT (debug binaries are not useful to the user)
```
find . -name "*_debug*" -print0 | xargs -0 rm -rf 
#find . -name "*_debug*" -type f -print0 | xargs -0 rm -rf
find . -name "*.dSYM" -print0 | xargs -0 rm -rf
find . -name "*.*.dSYM" -print0 | xargs -0 rm -rf
find . -name "*.prl" -print0 | xargs -0 rm -rf
```

### DESTROY ALL HEADERS. (No reason to deploy headers, only binaries are loaded)
```
find . -type d -name "Headers" -print0 | xargs -0 rm -rf
find . -type f -name "Headers" -print0 | xargs -0 rm -rf
```
