#
# Compiler flags
#
CC     = clang++
CXXFLAGS = -fPIC -Wall -Qunused-arguments  -std=c++11 -I../include \
		   								        -I./
LDFLAGS = -shared
TARGET_LIB = libcci_complx.so
#
# Project files
#
SRCS = c++complexity.cpp
OBJS =  c++complexity.o
# Debug build settings
#
DBGDIR = debug
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCFLAGS = -g -O0 -DDEBUG -pg 
DBGLIB = $(DBGDIR)/$(TARGET_LIB)
#
# Release build settings
#
RELDIR = release
RELLIB = $(RELDIR)/$(TARGET_LIB)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCFLAGS = -O3 -DNDEBUG

.PHONY: all clean debug prep release remake

# Default build
all: prep release debug

#
# Debug rules
#
debug: $(DBGLIB)

$(DBGLIB): $(DBGOBJS)
	$(CC) $(CXXFLAGS) $(DBGCFLAGS) $(LDFLAGS) -o $(DBGLIB) $^
	cp $(DBGLIB) ../lib

$(DBGDIR)/%.o: %.cpp
	$(CC) -c $(CXXFLAGS) $(DBGCFLAGS) -o $@ $<

#
# Release rules
#
release: $(RELLIB)

$(RELLIB): $(RELOBJS)
	$(CC) $(CXXFLAGS) $(RELCFLAGS) $(LDFLAGS) -o $(RELLIB) $^

$(RELDIR)/%.o: %.cpp

	$(CC) -c $(CXXFLAGS) $(RELCFLAGS) -o $@ $<

#
# Other rules)
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR)

remake: clean all

clean:
	rm -f $(RELOBJS) $(DBGOBJS) \
		  $(DBGDIR)/$(TARGET_LIB) $(RELDIR)/$(TARGET_LIB) \
		  $(DBGLIB) $(RELLIB)


