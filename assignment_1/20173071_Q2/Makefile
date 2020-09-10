###############################################################################
# File        : Makefile                                                      #
# Author      : Aditya Saripalli                                              #
# Description : A generic Makefile for building any c++ project with the      #
#               following directory structure.                                #
#               ./src                                                         #
#               ./obj                                                         #
#               ./bin                                                         #
###############################################################################

TARGET  = bigint
CC      = g++
CCFLAGS = -Wall -std=c++1z
SRCDIR  = ./src
OBJDIR  = ./obj
BINDIR  = ./bin

FILES   := $(wildcard $(SRCDIR)/*.cc)
OBJECTS := $(FILES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
	@echo "Linking Complete."
	@echo "To start the \"BigInteger\" run --> "$(BINDIR)"/"$(TARGET)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CCFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully."

clean:
	@echo "Cleaning all the object files and binaries."
	rm -f core $(OBJECTS) $(BINDIR)/$(TARGET)
