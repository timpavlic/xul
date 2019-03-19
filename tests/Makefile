CXX ?= g++

CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra

SOURCES := test_static_pimpl.cpp

OBJDIR ?= objs

# Define the objects that the application will use. They are derived
# from the SOURCES variable, filtering out anything that is not
# a C or C++ source file, i.e., .c and .cpp files
OBJECTS += $(patsubst    %.cpp,    $(OBJDIR)/%.opp,    $(filter    %.cpp,    $(SOURCES)))
OBJECTS += $(patsubst    %.c    , $(OBJDIR)/%.o,    $(filter    %.c,    $(SOURCES)))

test : $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

# Ensure objects dir exists before trying to make any object
$(OBJECTS): | $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)


$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $? -o $@

# C++ object files are built from a corresponding .cpp file
$(OBJDIR)/%.opp : %.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@
