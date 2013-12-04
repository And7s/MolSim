

# Compiler
# --------
CC=g++
#CC=icpc

include files.mk


# Compiler flags
# -------------------------------------------------------------------------
CFLAGS=-g -O3 

# Linker flags
# ------------
LDFLAGS= -lxerces-c -Wl,--no-as-needed -lcppunit -lapr-1 -laprutil-1 -llog4cxx

INCLUDES= -I./src -I./libxsd

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MolSim


all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

clean:
	rm $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

