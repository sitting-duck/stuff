### Chapter 2

Two key Photoshop concepts are containment structures and inheritance hierarchies.

These structures reveal how Photoshop organizes its information about:
documents
layers
channels
selections 
commands
filters
action events

Containers define what elements hold other elements. Containment structures hold independent objects that may or may not inherit properties from the container. 

Inheritance Hierarchies define what parameters or properties are available to the objects or subclasses held in containers. Inheritance hierarchies define what properties are inherited from one subclass to another. 

Note: all of the base classes in the inheritance hierarchies are in fact abstract classes, so deriving objects from them is impossble. And keep in mind that some of the base classes will require general parameters to exist in all classes derived from them. 

### Photoshop Containment Structure

Photoshop can hold menus, actions and a document. 

A document can hold layers, channels, guides, etc. 

Any given selection will be within a channel or layer within a document. 

An action, ecent, command or function will 'act' on a section in the document. 

Selections can be explicitly defined or assumed to be the current or last defined selection. 

A channel be itself a document, and also a child of a layer. For me, this is not difficult to understand at all but I can see how this nuance could be confusing. 

### 2. Photoshop Object Model

Containment Hierarchy:


Photoshop ---- Menu
            |
            -- Action -- Command
            |
            -- Document -- Layer -- Channel
                        |
                        -- Guide
                        |
                        -- Channel



These are all the elements that can contain other elements. 

Some elements are required to contain some, but not all, of the other elements. 

For instance, all documents are required to have at least one layer, but a document doesn't require a guide.

A layer must contain at least one channel, as another example. 

Example Inheritance Model 

Color
	RGB
	CMYK
	Unspecified
	Grayscale
	HSB
	Lab
	Book

and so on....

whenever an action is performed on an object, Photoshop works its way up the target chain, starting with the currently selected object, until it finds a container with the appropriate object. 

### Element Inheritance

Element
    |
    --- Application
    ---	Document
    --- Layer       --- Adjustment Layer
		    --- Bkg. Layer

    --- Channel
    --- Command
    --- Action
    --- Channel
    --- Guide
    --- Menu

Every Photoshop Element inherits the parameters of its parent element or gropus. eg. The adjustment layer class inherits all the params of its parent layer class.


### Color Inheritance Hierarcy

actually pretty self explanatory

Color
	RGB
	CMYK
	Unspecified
	Grayscale
	HSB
	Lab
	Book

### Mode Inheritance Hierarchy

Mode inheritance adjusts the channels and what they represent in the document. A document can only be in one mode subclass at a time 


Mode 
	RGB Color
	Bitmap
	Grayscale
	Indexed Color
	Duotone
	Lab Color
	CMYK Color
	Multichannel Color

I have a feeling this might be tricky for me to understand? It honestly looks pretty closely related to color encoding schemes, and this I guess makes sense because different color schemes have a different number of channels. 

### Adjustment Inheritance Hierarchy

Adjustment
	Invert
	Levels
	Curves
	Brightness/Contrast
	Color Balance
	Hue Saturation
	Selective Clr.
	Threshold
	Posterize

### Format Inheritance Hierarchy

The format hierarchy defines all the possible types of files Photshop can read and write. 
A file bay be saved in any of these formats, and this process can easily be automated to proved an action that can save multiple file formats with one command. There are also plugin file formats. 

Format
	Photoshop 4
	Photoshop PDF
	Photoshop 2
	Scitex CT
	EPX PICTS Preview
	EPS TIFF Preview
	EPS Generic
	PICT File
	Raw
	TIFF
	PICT Resource
	JPEG
	Phopshop EPS

### Actions and Targets
	The concepts of containment and inheritance come into play when considering an action and its target. The idea of containment is: a channel is contained in a document or a layer. A layer is contained in a document. A selection is contained in a layer or a channel etc. An action can "act" on a target, and that target can be specified in detail. ie. document, layer, channel, selection etc. But it is convenient to make some assumptions about the target where possible. For example, when executing a blur on a selection, it is convenient to assume that the blur will be on the current selection and leave it at that. 

Photo actions engine gets a command with no specific selection, and it parses the request by moving up the containmnet chain until it finds an element that firs the target. If the command were gaussian blur with radius 2.6 pixels, Photosohp moves up the chain of containers until it finds an element that understands the filter Gaussian Blur, and then works its way down the chain of containers until it finds a layer or channel that can be "blurred"

### Targets
	Targets are the frontmost item in Photoshops current state. Every time the user clicks on a different layer or moves to another document, the target changes. 

Actions are performed on the current targt, and it is possible to define other targets and attach them to descriptors for propert playback. You can switch targets, play an action, then switch again to perform another action on another target all by changing the target reference.

PS looks first for keyTarget at the befinning of every descriptor block, and if it finds one, it sends the command to that target.

If the target gets an action it is unable to perform, eg. a layer getting a command to open a document, clearly this is not something a layer is capable of doing, so it will pass the action to its container object. Photoshop will search all of the objects starting with the current target until a container is found that can hold the object being manipulated. 

This link of container objects is called the target chain, and it is always present in Photoshop. For instance, if you have a channel selected as the current target, then the target chain is Channel -> Layer -> Document -> Photoshop. In this case, it is PS itself that knows how to handle the open command. 

The target reference value can be one of three things: a complete path, a partial path, or NULL. Each value type is handled differently. 

If the reference is a complete path, then the target that is defined by that path recieves the action, and all is well. In the case where the reference is a partial path, the first target up the calling chain that can handle the path takes the command. This is important, because it stops at the first one it finds, so don't be surprised if you have duplicates and it doesn't stop at the one you wanted, bc you got confused. Just keep your target chain organized, and you'll be fine.

target value is NULL or dne then we just go up the chain from the current target (last selected item)

### Handling User Interaction While Playing An Action

Handling user interaction during exceptions or unpredicted circumstances while playing an action is done by choosing one of three modes under which an action can execute. 

UI Mode
No UI Mode
Silent Mode
I
Each mode performs the given action, but provides info to the user at diferent times and in different ways. 

### UI Mode

UI mode will execute an action and display the related dialog box for every step in the action. 
eg. a filter action will pop up a filter box window asking for the params. This method is the most error - free, but the least automated. 

### No UI Mode

	It relies on the values passed in by the descriptor block and not requiring interaction. It may pop up a dialog if the routine comes accross values that are invalid for execution and that connot be coerced into valid values. It will also display dialogs for where the descriptor is incomplete. Automation is higher, engagement is minimal. This is the stuff typically played in Photoshop's Actions Palete, unless logging is otherwise specified. In that case, Silent Mode is the mode of execution. 
 
### Silent Mode

	 Silent Mode allows you to completely automate regardless of states in Photoshop. If an error or other exceptional cases arises while in execution of an action, the routin will pass back the error message in the key 'keyMessage'. A somewhat odd name for a var that holds error values :/

No user interaction, but it is the most likely to return bad images, because there is no validation from the user at every step. 

It just proceeds with the next command even after a command has failed. 

### Elements, Classes, References, and Target Paths

	Action: a set of one or more Photoshop events with target elements and parameters. 

	Event: A basic Photoshop command or instruction that is accessible by an automation plug-in. Events act on elements.

	Element: An elem keyent consists of objects and classes and represents a tangible object inside Photoshop. Events act on elements and elements can be created, acted upon, saved in a file or destroyed. Elements can be simple objects (selections, colors, etc) or they can be composed of lists of multiple objects with varied class parameters.

	Class: A predefined set of Photoshop parameters that are logically connected to an object. For example, the classLayer has a set of subclasses including class TextLayer, classBackgroundLayer, classAdjustmentLayer etc. The Rectangle class always consists of four number elements top, left, bottom and right.

	Target: the object of a Photoshop event. 

	Target Path: aka keyTarget. The relative path to a given selection. If no explicit path is given for a target in the action or event, Photoshop works its way up the containment hierarchy structure intil it finds a suitable object for the action or event. for example, if the action is a blur on a selection a channel, Photoshop looks for an element that recofnizes a chennel, then looks for the specified selection.

	Reference: a target path through the Photoshop containment hierarchy.

	This is pretty high level. Writing a new auto plugin requires a high level of detail :(
	The next chapter steps through the details of writing an automation plugin. 

  
