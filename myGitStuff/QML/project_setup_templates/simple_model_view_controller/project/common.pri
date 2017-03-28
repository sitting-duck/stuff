# common project config settings. All subdirs in this project will use these settings.

INCLUDEPATH += .
WARNINGS += -Wall

# creates a makefile to build a library
TEMPLATE = lib

# the following keeps the generated files at least somewhat separate from the source files.
UI_DIR = uics		# TODO: figure out what this does and document it
MOC_DIR = mocs		# dir to contain files made by the meta object compiler.  The meta object compiler compiles QT classes.
OBJECTS_DIR = objs	# dir to contain object files. object files are intermediate steps between source and binary files

