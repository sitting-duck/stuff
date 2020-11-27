https://docs.conan.io/en/latest/creating_packages/understand_packaging.html

### Understanding Packaging

### Creating and testing Packages Manually
The previous create approach using test_package subfolder, is not strictly necessary, though very strongly recommended. If we didn't want to use the test_package functionality, we could just write our recipe ourselves or use the ``conan new`` command without the ``-t`` command line argument.

```
mkdir mypkg && cd mypkg
conan new hello/0.1
```

This will create the conanfile.py recipe file. Now we can create our package: 
```
conan create . demo/testing
```
Once the package is created, it can be consumed like any other package, by adding ``hello/0.1@demo/testing`` to a project conanfile.txt or a conanfile.py requirements and running: 
```
conan install . 
# build and run  your project to ensure the package works
```
### Package Creation Process
It is very useful for package creators and Conan users in general to understand the flow for creating a package inside the conan local cache, and all about its layout. 

Each package recipe contains five important folders in the local cache: 

**export** - the folder in which the package recipe is stored

**export_source** - the folder in which code copied with the recipe ``export_sources`` attribute is stored. 

**source** - the folder in which the source code for building from sources is stored

**build** - the folder in which the actual compilation of sources is done. There will typically bee one subfolder for each different binary configuration

**package** - the folder in which the final package artifacts are stored. There will be one subfolder for each different binary configuration. 

The source and build folders only exist when the packages have been built from sources. 

(https://docs.conan.io/en/latest/_images/conan-package_create_flow.png
)[]

It appears that each build and therefore each package has a unique hash.

The process starts when a package is "exported" via the``conan export`` or more typically with the ``conan create`` command. The conanfile.py and files specified by the ``exports_sources`` field are copied from the user space to the local cache.

The export and export_source files are copied to the source folder and then the ``source()`` method is executed (if it exists). Note that there is only one source folder for all the binary packages. If when generating the code, there is source code that varies for the different configurations, it cannot be generated using the ``source()`` method, but rather needs to be generated using the ``build()`` method.

Then for each different configuration of settings and options, a package ID will be computed in the form of a SHA 1 hash for this configuration. Sources will be copied to the build/hashXXX folder.

Finally the package_info() methods for all dependencies will be called and gathered so you can generate files for the consumer build system as the conanbuilidinfo.cmake for the ``cmake`` generator. Also the ``imports`` feature will copy artifacts from the local cache into the user space if specified.


