This was one of the first side project I made when learning QML. 

When I first started writing QML, my first assumption was that C++/QML integration was going to be suuuuuper important. <br/>
I had figured that all of the heavy lifting would be done on the C++ side, and that QML would be written only for visual elements. <br/>
The base class of all base classes for QT is caled QtObject and it only has one property objectName. <br/>
This meant that this objectName property would always be accessible from either C++ or QML. <br/>

In my experience writing Android code, I found that I often passed variables between layout files, and executing Java code files
pretty much all the time, so I expected that would be the case here. 

It turns out this was not to be. The employee that had been at the company the longest at the time only wrote in QML.
This meant that if it wasn't written by the image processing phd types, and it wasn't file io related, it was probably written
in QML. 

This class turned out to never really be useful to me at all. On top of that, when I submitted it to the repo ...

