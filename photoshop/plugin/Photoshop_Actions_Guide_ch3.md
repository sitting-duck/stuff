### Creating an Automation Plugin

this ch covers the basics of writing an auto plugin and the various data structures and interrelationships between host, automation plugins, and old style plugins. 

### Standard Plugins vs Automation Plugins

Just looking at the diagram for automation plugins makes it really very apparent how much more complex and versatile they are then regular Photoshop plugins. Am I even sure I am in the right place then? Am I looking at the right thing? What kind of plugin do we have and what the fuck is it?

### Photoshop 5 Organization

Version 2: PS pioneered the concept of a host/plugin module architecture that spurred the development of many innovative third party plugins. As PS matured, the plugin arch was revided to provide more robust structures. By version 4, PS itself was extensively revised internally to be more object oriented, and this restructuring was exploited for the users benefit in the new Actions Palette. In Version 5 the automation plugin arch can now be exploited by external plugins. PS include the traditional code to access old style plugins as well as new ways to access the new automation Actions Engine. 

The Automation Engine and os 5's actions hierarchical architecture are part of what enables the creation of automation plugins. the other part is the PICA suite-based plugin architecture. 

### Plugin Component Architecture (PICA)
provides a way to commo with internal and third party plugins for several Adobe applications. 
PICA does cross platform shit for you like the ADM Adobe Dialog Manager, which will let you write some GUI code probably for PS. 

### Plugin Data Structures (PIPLs and Suites)
Key Automation plugin data structures are the PiPL plugin properties list and the message structures and suites used by PICA. 


### PiPls
	
