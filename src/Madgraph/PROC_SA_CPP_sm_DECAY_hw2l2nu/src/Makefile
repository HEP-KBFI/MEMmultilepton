LIBDIR=../lib
CXXFLAGS= -O -I.

target=$(LIBDIR)/libmodel_sm_hw2l2nu.a

all: $(target)

objects=HelAmps_sm_hw2l2nu.o Parameters_sm_hw2l2nu.o  ../../PROC_SA_CPP_sm_4/src/read_slha.o

$(target): $(objects)
	mkdir -p $(LIBDIR)
	$(AR) cru $@ $(objects)
	ranlib $(target)

.PHONY: clean

clean:
	rm -f $(target)
	rm -f $(objects)

