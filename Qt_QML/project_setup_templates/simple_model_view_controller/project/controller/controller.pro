# throw an exception if the common.pri file is not in the project directory and include it in this project
# the common.pri file contains all the project config settings that are common across all subprojects
! include(../common.pri){ error("ERROR: MISSING COMMON.PRI FILE") }

CONFIG += staticlib
TEMPLATE = lib
TARGET = ./../../build/executable