LIBDIR=../../lib
INCDIR=../../src
MODELLIB=model_sm_gqlnullgq
CXXFLAGS= -O -I$(INCDIR) -I.
LIBFLAGS= -L$(LIBDIR) -l$(MODELLIB)

main=CPPProcess_P0_Sigma_sm_gdx_epvemupmumgux.o

all: $(main)

objects=CPPProcess_P0_Sigma_sm_gdx_epvemupmumgux.o 

#$(main): $(objects) $(LIBDIR)/lib$(MODELLIB).a
#	$(CXX) -o $@ $(objects) $(LIBFLAGS)

$(LIBDIR)/lib$(MODELLIB).a:
	cd ../../src
	make

.PHONY: clean

clean:
	rm -f $(target)
	rm -f $(objects)

