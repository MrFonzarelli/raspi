# Makefile for the raspi project

PROG = raspi
SRCDIR = src
OBJDIR = obj
DATADIR = data
CXX = g++
INCDIRS = $(shell find $(SRCDIR) -type d)
INCFLAGS = $(addprefix -I,$(INCDIRS))
LDFLAGS = -lwiringPi -lpthread 
CXXFLAGS = -O2 -pipe -pthread -std=c++17 $(INCFLAGS)
DEPFLAGS = -MMD -MP
SRCS = $(shell find $(SRCDIR) -name *.cpp)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
STATICOBJS = $(addprefix $(OBJDIR)/,ssd1306_i2c.o)
DEPS = $(OBJS:.o=.d)

# Default target
all: $(PROG)

# Program target
$(PROG): $(OBJS) $(DATADIR) $(STATICOBJS)
	$(CXX) -o $(PROG) $(OBJS) $(STATICOBJS) $(LDFLAGS)

$(OBJDIR) $(DATADIR):
	@mkdir -p $@

$(OBJDIR)/ssd1306_i2c.o: src/ssd1306_i2c.c | $(OBJDIR)
	$(CXX) -c $< -o $@

%.o: %.cpp

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# Clean target
clean:
	@rm -rf $(OBJDIR) $(PROG)

.PHONY: all clean

-include $(DEPS)
