LIBDIR=../lib
CXXFLAGS= -O -I.

target=$(LIBDIR)/libmodel_sm_ggtt.a

all: $(target)

objects=HelAmps_sm_ggtt.o Parameters_sm_ggtt.o  ../../PROC_SA_CPP_sm_4/src/read_slha.o

$(target): $(objects)
	mkdir -p $(LIBDIR)
	$(AR) cru $@ $(objects)
	ranlib $(target)

.PHONY: clean

clean:
	rm -f $(target)
	rm -f $(objects)

