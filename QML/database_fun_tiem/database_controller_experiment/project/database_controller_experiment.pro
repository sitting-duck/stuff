TEMPLATE = subdirs

OTHER_FILES +=  common.pri 

SUBDIRS += \
    model \			# build models first, which will manipulated by controllers
	controller \	# build controllers second, which will manipulate models
    view			# build views last, which will display models and use controllers


# When using the subdirs template, this option specifies that the directories
# listed should be processed in the order in which they are given.
CONFIG += ordered

# app must always be the last item in subdirs variable.  It should always be built last because it depends on
# things in the controller, model, and view subdirs
SUBDIRS += app
