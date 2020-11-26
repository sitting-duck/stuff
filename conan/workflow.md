#Workflows

https://docs.conan.io/en/latest/using_packages/workflows.html

Suggested to have a conanfile.py or .txt at the root of your project. 

# Creating Packages
https://docs.conan.io/en/latest/creating_packages.html

### Getting Started
```
conan new hello/0.1 -t
```
create a new package called hello
It will make your conanfile.py and test_package and 
CMakeLists.txt and so on

Once you make the conanfile.py and all your sources are accounted for you can call: 
```
conan create . demo/testing
```
where demo is the user and testing is the channel

and that will build the source, create the package and copy it to your local cache

This command is equivalent to: 
```
conan export . demo/testing
conan install hello/0.1@demo/testing --build=hello
# package is created use test to test it
conan test test_package hello/0.1@demo/testing
```
Search for a package
```
conan search packagename/1.0@
```

Removing Packages:
```
conan remove packagename/1.0
```

Uploading Packages:
```
conan upload packagename/1.0
```

If many packages use the same option, you can set all of them using a pattern like this: 
```
conan install . -o *:shared=True
```


