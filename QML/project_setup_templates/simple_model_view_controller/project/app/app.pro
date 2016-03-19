
# specifies that this module contains the entry to the application
TEMPLATE = app

SOURCES += main.cpp

# grab the model, view, and controller libraries
LIBS += -L/../model -L/../controller -L/../view 

#where to build the final executable
TARGET = ./../../build/executable
