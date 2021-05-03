
### Search Remote Conan Repo
```
conan search searchPhrase --remote=conan-center
```
Official docs reccomend using the Conan Center UI though ;_; lame sauce.

### Print Some Info about A Package
```
conan inspect poco/1.9.4
```
poco/1.9.4 just picked to show as an example. Put whatever package you care about here.

### Conan Show My Profile
```
conan profile show default
```
Conan will detect stuff and make a default one for you, but you should check it and make sure it is right, it might set gcc as your compiler when you want apple-clang for example, or whatever. 

### Search Local Packages
```
conan search "searchphrase"
```

### Show All the Packages in the Project
```
conan info /path/to/conanfile.txt/containing/folder/
```
pass in a folder that contains the conanfile.txt file for that project

### Generate a graph of your dependencies using HTML
```
conan info /path/to/conanfile.txt/containing/folder/ --graph=file.html
```
cute.

### Show All Remotes
```
conan remote list
```
### Show all the packages in my local artifactory
```
conan search -r artifactory "*"
```

### Install
pip3 install -U --user conan
conan --version

### Configure Conan
conan remote remote conan-center # if you only want to pull from your own artifactory for example

### Add remote
conan remote add artifactory http://my.address:8080/artifactory/api/conan/

### Login
conan user -p <password> -r artifactory <username>
conan config init
conan config set general.revisions_enabled=1

More note: 
# copy into conan/profiles so you don't have to type the path everytime
cp /e/project/_util/conan/profile_win2019 ~/.conan/profiles/


conan export-pkg ./conanfile.py angine/2.0.0@ashley/testing -pf . -f
conan export-pkg ./conanfile.py ashley/testing -pf . -f
conan upload libomp/1.0@ -r artifactory --all
conan export-pkg ./conanfile.py engine/2.0.0@ashley/testing -f -pr ./../../project/_util/conan/profile_win2019




# if you're in the same folder fstudio is which you should be it'd be 
conan install .\project\<app>\conanfile.py -if conan -pr .\fStudio\_util\conan\profile_win2019 
conan install ./project/denoise/conanfile.py -if conan -pr ./fStudio/_util/conan/profile_mac12.0
mklink /D libs .\conan\libs

### Build in Debug
```
conan install . -s build_type=Debug --build=missing
```

### Upload the Lib you just built from source
```
conan upload opencv/4.5.1@ -r my-remote-repo --all
```
