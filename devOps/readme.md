If you deploy environment is QT 5.12, and because you have been manually copying in dylibs when you make new deploy environments, you somehow missed or 
forgot one, so now your whole thing is using Qt 5.12, but one of your dylibs is still on 5.6, you will see an error on application load like: 

```
This application failed to start because it could not find or load the Qt platform plugin "cocoa".
```
This is such a red herring. Don't go inspecting CoaCoa, trying to rebuilt Qt, blah blah blah, this is caused by the dylib version mismatch, which, again, 
is something that can easily happen. Instead, do this:

```
  find . -type f -name "*.dylib" -print0 | xargs -0 otool -L {} | grep "5.6.3"
``` 
 
This little snippet is super useful for finding a needle in a haystack: 
Recursively search the otool output of all the dylibs in a folder for something.
This saved me so much time I can't even believe it. You kind of have to know what you're looking for though, 
because you have to know what to grep for. So, you have to have some idea of which version the contaminant dylib is.
  
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
