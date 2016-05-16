LLVM_CONFIG?=llvm-config


ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
LDFLAGS+= -L/dev_tools/lib -lglib-2.0 
COMMON_FLAGS= -Wall -std=c++11
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags) 
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR) \
		  									 -I../../include \
											 -I/usr/lib/llvm-3.6/include \
											 -I/usr/include/glib-2.0 \
											 -I/usr/lib/i386-linux-gnu/glib-2.0/include

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
LLVMLIBS=$(shell $(LLVM_CONFIG) --libs)
SYSTEMLIBS=$(shell $(LLVM_CONFIG) --system-libs)

CLANG_MINI_DIAG=clang-mini-diag
CLANG_MINI_LEX=clang-mini-lex
CLANG_MINI_DIAG_OBJECTS=clang_mini_diag.o mini_diag_main.o
CLANG_MINI_LEX_OBJECTS=clang_mini_lex.o mini_lex_main.o
CLANG_MINI_DRIVER=clang-mini-driver
CLANG_MINI_DRIVER_OBJECTS=clang_mini_driver.o mini_driver_main.o

default: all

all : $(CLANG_MINI_DIAG) $(CLANG_MINI_LEX) $(CLANG_MINI_DRIVER)


%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp	
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(CLANG_MINI_DIAG) : $(CLANG_MINI_DIAG_OBJECTS)
	@echo Linking $@
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS) $(SYSTEMLIBS)

$(CLANG_MINI_LEX) : $(CLANG_MINI_LEX_OBJECTS)
	@echo Linking $@
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS) $(SYSTEMLIBS)

$(CLANG_MINI_DRIVER) : $(CLANG_MINI_DRIVER_OBJECTS)
	@echo Linking $@
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS) $(SYSTEMLIBS)


clean::
	$(QUIET)rm -f $(CLANG_MINI_DIAG) $(CLANG_MINI_DIAG_OBJECTS) \
				  $(CLANG_MINI_LEX) $(CLANG_MINI_LEX_OBJECTS) \
				  $(CLANG_MINI_DRIVER) $(CLANG_MINI_DRIVER_OBJECTS) 
