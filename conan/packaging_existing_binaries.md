https://docs.conan.io/en/latest/creating_packages/existing_binaries.html

There are specific scenarios in which it is neccessary to create packages from existing binaries, for example from 3rd parties of binaries previously built by another process or team that are not using Conan. Under these circumstances building from sources is not what you want. You should package the local files in the following situations.

- when you cannot build the packages from sources
- when you are developing your package locally and you don't want to export the built artifacts to the local cache. As you don't want to rebuild again (clean copy) your artifacts, you don't want to call ``conan create``. This method will keep your build cache if you are using an IDE or calling locally to the ``conan build`` command.

### Packaging Pre-built Binaries
Running the ``build()`` method, when the files you want to package are local results in no added value as the files copied from the user folder cannot be reproduced. For this scenario, run ``conan export-pkg`` command directly. 

A conan recipe is still required, but it is very simple and will only include the package meta information. A basic recipe can be created with the ``conan new`` command.
```
conan new hello/0.1 --bare
```

This will create and store the following package recipe in the local cache: 
```
class HelloConan(ConanFile):
name = "hello"
version = "0.1"
settings = "os", "compiler", "build_type", "arch"

	def package(self):
		self.copy("*")

	def package_info(self):
		self.cpp_info.libs = self.collect_libs()


```

The provided ``package_iinfo()`` method scans the package files to provide end users with the name of the libraries to link. This method can be further customized to provide additional build flags (typically dependent o n the settings.) The default ``package_info()`` applies as follows: it defines headers in the include folder, libraries in the lib folder, and binaries in the bin folder. A different package layout can be defined in the package_info() method. 

This package recipe can also be extended to provide support for more configurations (for example, adding options: shared/static, or using different settings) adding dependencies (``requires``) and more.

Based on the above, We can assume that our current directory contains a lib folder with a number of binaries for this "hello" library libhello.a

Having a test_package folder is still highly recommended for testing the package locally before upload. As we do't want to build the package from the sources, the flow would be: 
```
conan new hello/0.1 --bare --test
cd my/path/to/binaries
conan export-pkg /PATH/TO/conantfile.py hello/0.1@myuser/testing -s -os=Windows -s compiler=gcc compiler.version=4.9 ...
conan test PATH/TO/test_package/conanfile.py hello/0.1@myuser/testing -s os=Windows
```

The last two steps can be repeated for any number of configurations. 

### Downloading and Packaging Pre-built Binaries
In this scenario, creating a complete Conan recipe, with the detailed retrieval of the binaries could be the preferred method, because it is reproducible and the original binaries might be traced. Follow our sample recipe for this purpose:

```
class HelloConan(ConanFile):
	name = 'hello'
	version = "0.1"
	settings = "os", "compiler", "build_type", "arch"

	def build(self):
		if.self.settings.os == "Windows" and self.settings.compiler == "Visual Studio":
		url = (https://<someurl>/downloads/hello_binary%s_%s.zip"
		elif ...
		else:
			raise Exception("Binary does not exist for these settings")
		tools.get(url)
	
	def package(self):
		self.copy("*")

	def package_info(self):
		self.cpp_info_libs = ["hello"]
```

Typically, pre-compiled binaries come for different configurations, so the only task that the build() method ahas to implement is to map the ``settings`` to the different URLs.




