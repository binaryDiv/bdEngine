# == CG_Projekt Makefile ==

# GL
GL_LIBS := $(shell pkg-config --libs glfw3 glew)
GL_INCLUDES := $(shell pkg-config --cflags glfw3 glew)

# C++ flags
CXX := clang++
CXXFLAGS := -std=c++14 -O2 -g -Wall -pedantic
LIBS := $(GL_LIBS)
INCLUDES := $(GL_INCLUDES)

# Project directories
SRCDIR := src
BUILDDIR := build
BINDIR := bin

# Target variables
TARGET := $(BINDIR)/testgame
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
CLEANDELETE :=

HEADERS := $(shell find $(SRCDIR) -type f -name *.h)
SOURCEDEPS := $(HEADERS)

# MAKE TARGETS
# ------------

# Default 'all' target
all: testgame

testgame: $(TARGET)

# Object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@#echo '$(CXX) -c $$(CXXFLAGS) $$(INCLUDES) -o $@ $<'
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -o $@ $<

# App target
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@#echo '$(CXX) $$(LIBS) -o $(TARGET) $(OBJECTS)'
	$(CXX) $(LIBS) -o $(TARGET) $(OBJECTS)

# Clean generated files
clean:
	rm -r $(BUILDDIR)
	rm -f $(TARGET) $(CLEANDELETE)

echoflags:
	@echo 'CXXFLAGS := $(CXXFLAGS)'
	@echo
	@echo 'LIBS := $(LIBS)'
	@echo
	@echo 'INCLUDES := $(INCLUDES)'
	@echo

.PHONY: all clean echoflags
