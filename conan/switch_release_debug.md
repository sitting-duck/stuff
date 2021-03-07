```
# Open a cmd.exe as Administrator Windows

brek=RMDIR /Q C:\Users\ashley\projects\image\libs
doskey mkdbg=MKLINK /D C:\Users\ashley\projects\image\libs C:\Users\ashley\projects\image\conan_debug\libs
doskey mkrel=MKLINK /D C:\Users\ashley\projects\image\libs C:\Users\ashley\projects\image\conan\libs


### Switch to Debug
RMDIR /Q C:\Users\ashley\projects\image\libs
MKLINK /D C:\Users\ashley\projects\image\libs C:\Users\ashley\projects\image\conan_debug\libs

### Switch to Release
RMDIR /Q C:\Users\ashley\projects\image\libs
MKLINK /D C:\Users\ashley\projects\image\libs C:\Users\ashley\projects\image\conan\libs
```
