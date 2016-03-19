TEMPLATE = subdirs

OTHER_FILES +=  common.pri \
                main.qml

SUBDIRS += \
    controller \
    model \
    view \
    app

# When using the subdirs template, this option specifies that the directories
# listed should be processed in the order in which they are given.
CONFIG += ordered

