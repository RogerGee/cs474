################################################################################
# makefile for 'pokfactory' ####################################################
################################################################################
.PHONY: clean

ifeq ($(MAKECMDGOALS),debug)
MAKE_DEBUG = yes
endif

# options
SRC = ../src
MACROS = BLAHBLAHBLAH
CFLAGS = -Wall -pedantic-errors -Werror -Wextra -Wshadow\
	-Wfatal-errors -Wno-unused-parameter -std=c++11
INCLUDE = -I$(SRC)
ifdef MAKE_DEBUG

MACROS := $(MACROS) POKFACTORY_DEBUG
PROGRAM = pokfactory-debug
OBJDIR = dobj
COMPILE = g++ -c -g $(CFLAGS) $(INCLUDE) $(addprefix -D,$(MACROS))
LINK = g++

else

PROGRAM = pokfactory
OBJDIR = obj
COMPILE = g++ -c -O3 $(CFLAGS) $(INCLUDE) $(addprefix -D,$(MACROS))
LINK = g++ -s

endif

# targets
TARGETS = pokfactory region region-factory
OBJS = $(addprefix $(OBJDIR)/,$(addsuffix .o,$(TARGETS)))

# dependencies
POKEMON_H = $(SRC)/pokemon.h
REGION_FACTORY_H = $(SRC)/region-factory.h $(POKEMON_H)
REGION_H = $(SRC)/region.h $(REGION_FACTORY_H)

# rules
all: $(OBJDIR) $(PROGRAM)
debug: $(OBJDIR) $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(LINK) -o$@ $(OBJS) $(LIBS)

$(OBJDIR)/pokfactory.o: $(SRC)/pokfactory.cpp $(REGION_FACTORY_H)
	$(COMPILE) -o$@ $<
$(OBJDIR)/region.o: $(SRC)/region.cpp $(REGION_H)
	$(COMPILE) -o$@ $<
$(OBJDIR)/region-factory.o: $(SRC)/region-factory.cpp $(REGION_FACTORY_H)
	$(COMPILE) -o$@ $<

$(OBJDIR):
	mkdir $(OBJDIR)
