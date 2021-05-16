This was one of the first side project I made when learning QML. 

When I first started writing QML, my first assumption was that C++/QML integration was going to be suuuuuper important. <br/>
I had figured that all of the heavy lifting would be done on the C++ side, and that QML would be written only for visual elements. <br/>
The base class of all base classes for QT is caled QtObject and it only has one property objectName. <br/>
This meant that this objectName property would always be accessible from either C++ or QML. <br/>

In my experience writing Android code, I found that I often passed variables between layout files, and executing Java code files
pretty much all the time, so I expected that would be the case here. 

This class turned out to never really be useful to me at all because it didn't go with the paradigm of most of the code base at work, and was based a on a false assumption of mine that every object in QML should have an id. It was a nice little kata in Python, but I have yet to have found an actual use for it.
I was also trying to learn Python at the time I wrote this, so it is not an example of good python code, but I will keep it in my notes regardless as an example to learn from.

```
Rectangle {
  id: Rectangle1
  objectName: "Rectangle1"
}
```

So every QML object can be given an id, and inside of each scope, each is must be unique.
It made a lot of sense to me at the time, that I could grab whatever GUI element I need from the GUI side by object name this way.
I figured I could recursively run this script, and process every qml file in my repository, so that every GUI element could be
easily accessed on the C++ side this way. 

Again, never turned out that way, but you get the idea.

You can see a super simple example input qml file in test.qml, 
and you can see what the expected output would be with new_test.qml

