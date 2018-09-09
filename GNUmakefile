# --------------------------------------------------------------
#  # GNUmakefile for a basic module.  Xiandong Zhao, 10/04/2017.
# --------------------------------------------------------------

name := rutherfordG4
G4TARGET := $(name)
G4EXLIB := true

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)
CPPFLAGS += $(ROOTCFLAGS)
EXTRALIBS += $(ROOTLIBS) $(ROOTGLIBS)

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk
