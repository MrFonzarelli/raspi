# Makefile for the raspi project

PROG = raspi
SRCDIR = src
OBJDIR = obj
DATADIR = data
CXX = g++
INCDIRS = $(shell find $(SRCDIR) -type d)
INCFLAGS = $(addprefix -I,$(INCDIRS))
LDFLAGS = -lwiringPi
CXXFLAGS = -O2 -pipe -pthread $(INCFLAGS)
DEPFLAGS = -MMD -MP
SRCS = $(shell find $(SRCDIR) -name *.cpp)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

# Default target
all: $(PROG)

# Program target
$(PROG): $(OBJS) $(DATADIR)
	$(CXX) -o $(PROG) $(OBJS) $(LDFLAGS)

$(OBJDIR) $(DATADIR):
	@mkdir -p $@

%.o: %.cpp

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# Clean target
clean:
	@rm -rf $(OBJDIR) $(PROG)

.PHONY: all clean

-include $(DEPS)