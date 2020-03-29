Published: 03/29/2020

Written in 
```
java 14 2020-03-17
Java(TM) SE Runtime Environment (build 14+36-1461)
Java HotSpot(TM) 64-Bit Server VM (build 14+36-1461, mixed mode, sharing)
```

Operating System:
```

      System Version: macOS 10.15.1 (19B88)
      Kernel Version: Darwin 19.0.0
```

note: get via command line using ``system_profiler SPSoftwareDataType``

Compile the program this way: 
```
javac Driver.java
javac Labrinth.java
```

You can't invoke a class that you have not yet compiled. You will probably see an error like this: 
```
Error: Could not find or load main class Driver
Caused by: java.lang.ClassNotFoundException: Driver
```
If you make this mistake

Invoke the program this way:

```
$ java -cp . Labrinth
```

The -cp flag stands for Class Path, we are just saying that the path to the folder where the classes are stored is ``.``
Feel free to use a different path as long as it points to the class file folder.




