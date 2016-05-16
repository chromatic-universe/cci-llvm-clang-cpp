LLVM_CONFIG?=llvm-config

ifndef VERBOSE
QUIET:=@
endif

#
# Compiler flags
#
SRC_DIR?=$(PWD)
CXX     = clang++
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
LDFLAGS+= -lACE -L$(DEV_LIB) 
COMMON_FLAGS=  -DACE_NTRACE=0 -Wextra -std=c++11 -fno-rtti -I$(ACE_ROOT) -Qunused-arguments 
CXXFLAGS+=$(COMMON_FLAGS)
#-rdynamic for jit
CXXFLAGS+= -I$(shell $(LLVM_CONFIG) --includedir) \
		   -rdynamic \
		   -D_GNU_SOURCE \
		   -D__STDC_CONSTANT_MACROS \
		   -D__STDC_FORMAT_MACROS \
		   -D__STDC_LIMIT_MACROS \
		   -g \
		   -O0 \
		   -fomit-frame-pointer \
		   -std=c++11 \
		   -fvisibility-inlines-hidden \
		   -fno-exceptions  \
		   -fPIC \
		   -ffunction-sections \
		   -fdata-sections \
		   -Wcast-qual 
CPPFLAGS+= -I../../include \
		   -I./ \
		   -I$(shell $(LLVM_CONFIG) --includedir) 
CLANGLIBS=\
  -Wl,--start-group\
  -lclang\
  -lclangFrontend\
  -lclangDriver\
  -lclangSerialization\
  -lclangParse\
  -lclangSema\
  -lclangAnalysis\
  -lclangEdit\
  -lclangAST\
  -lclangLex\
  -lclangBasic\
  -Wl,--end-group
LLVMLIBS=$(shell $(LLVM_CONFIG) --libs core mcjit native)
SYSTEMLIBS=$(shell $(LLVM_CONFIG) --system-libs)

TARGET_BIN = walk-a-baby 
#
# Project files
#
SRCS = walk_a_baby.cpp walk_a_baby_lex.cpp \
	   walk_a_baby_parse.cpp walk_a_baby_ast.cpp
OBJS = $(SRCS:.cpp=.o)

# Default build
default: $(TARGET_BIN)

%.o : $(SRC_DIR)/%.cpp
	@echo compiling $*.cpp	
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<


$(TARGET_BIN): $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS) $(SYSTEMLIBS) 

clean::
	$(QUIET)rm -f $(TARGET_BIN) $(OBJS)

