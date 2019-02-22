When I first started writing QML, I had trouble with Layouts. 
Layouts seem to fail silently in a way. The only indication that they have failed is that the GUI doesn't look right, 
but there is not always an error message that can be relied on. 

I would work around this by only making incremental changes and then testing after each change of course, but when editing 
pre-existing code with a lot of moving parts that I wasn't super familiar with yet,

I would find myself spending a lot of time trying to hunt down what worked and what didn't and become frustrated with the 
amount of time I spent on it. 

I started writing these GUI "Debug" classes, tools, functions, etc after work hours for printing out everything inside a QML object 
and I found the exercise to be quite instructive in not only 

a. understanding QML objects in general
b. getting a pretty quick picture of what was going on with QML element I was unfamiliar with without having to manually
type out just a million console logs.
