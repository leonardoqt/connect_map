ROOT_DIR=$(shell pwd)
ODIR  = $(ROOT_DIR)/obj
SDIR  = $(ROOT_DIR)/src
LDIR  = $(ROOT_DIR)/lib

CXX   = g++
CFLAG = -std=c++11
 
DEPS  = $(shell ls $(SDIR)/*.h)
SRC   = $(shell ls $(SDIR)/*.cpp)
OBJ   = $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))
LOBJ  = connector.o
LIB   = $(patsubst %.o,$(LDIR)/lib%.a,$(LOBJ))

test.x : $(OBJ) $(LIB)
	$(CXX) -o $@ $^ $(CFLAG)

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS) | $(ODIR)/.
	$(CXX) -c -o $@ $< $(CFLAG)

$(LDIR)/lib%.a : $(ODIR)/%.o | $(LDIR)/.
	ar -rcs $@ $<

%/. : 
	mkdir -p $(patsubst %/.,%,$@)
	
.PRECIOUS: %/.
.PHONY: clean clean_test clean_all
clean:
	rm -rf *.x $(ODIR) $(LDIR)
clean_all:
	rm -rf *.x $(ODIR) $(LDIR) *.*
