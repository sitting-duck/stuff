### Chapter 1:

This doc says I should first read the Photoshop 5.0 API guide. Although, this isn't really all that easy to find online so I shall move on. 

An automation plugin can interact with other plugins. That we knew. 
This tech is pretty powerful and is permitted by the actions engine. 

An Action is a data structure that contains an event, and a target. 

The Photoshop Object Model: 

Elements - include Objects, classes and functions. Actions are constructed from filters and commands (events and functions) with parameters that act on target selections (elements). 

Programmable Elements: are objects and classes that represent a tangible object inside Photoshop. Elements can be grouped into filters, tool classes, and events, element action events, document events, file action events, and classes and formats. Each element is unique with its own data types and functional capabilities, and elements can contain other elements.

Event Names: Unique strings, conventionally of 4 character length, but can be of any length. Every event has a corresponding target object, which is, by default, the last object selected. (eg. the current selection of the current layer of the current document)

Events can have optional parameters. eg. KeyRadius as a param being passed to a Gaussian Blur event. 

every param has an id, and a type. Of course, instead of using the actual float keyword, they use their own typedef, typeFloat, WHY DOES EVERYONE DO THIS?

An event has a Name: (macro event name)
eventName

Actual 4 character code: 'eventId'
'Name'

// here's what looks like a function definition, and inside the curlies is apparently what they call a "descriptor block"
eventName("Name")
{
keyTarget ("trgt")    reference     // optional TARGET reference
keyName ("key ID")    [pin values]  // optional key/value pair
('key constant')      [pint values] // additional key/value pairs
}

Example: 
Event: A Gaussian Blur of radius 2.6
Event ID/Name": eventGaussianBlur("GsnB")
Descriptor Block: 
{
keyRadius ("Rds ") 'typefloat ("Flt ") 2.6
}

Target: no specified target, so it will default to the current selection in the current layer of the current document
Parameters: There is one param in the descriptor block. It provides the param for the radius amount. In this case, there is one key ID and one type ID. The key ID is "Rds ", and then we have the id for the type "Flt " and then we have the value. 

There is one param. It has a key, and a type, they are specified on one line. They appear to follow the same, name, id convention as events. Alright, fine, I can deal with that, it seems like a bunch of shit I have to remember and kind of combersome, but I can deal. 

Event Names: As noted above, all elements and actionable bahaviors of Photoshop, including commands, fileters, objects, and classes have a unique four letter constant or "key" associated with them. While the ID code or key indicates the command or function, the specific parameters passed with the event define the specific Photoshop selection, element or function being acted upon as well as the actual paramaters of the function. 

The Descriptor Block: a list of key value pairs. First item is always the target, if any. Descriptors allow Photoshop to pass the params back and forth between the host editor and the plugin. 

Summary: This chapter briefly intro the internal structure of Photoshop. The next chapter explains the Photoshop Action Object Model in detail. 


