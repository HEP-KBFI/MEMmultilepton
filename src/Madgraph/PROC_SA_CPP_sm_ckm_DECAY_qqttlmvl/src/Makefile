LIBDIR=../lib
CXXFLAGS= -O -I.

target=$(LIBDIR)/libmodel_sm_ckm_qqttlmvl.a

all: $(target)

objects=HelAmps_sm_ckm_qqttlmvl.o Parameters_sm_ckm_qqttlmvl.o  ../../PROC_SA_CPP_sm_4/src/read_slha.o

$(target): $(objects)
	mkdir -p $(LIBDIR)
	$(AR) cru $@ $(objects)
	ranlib $(target)

.PHONY: clean

clean:
	rm -f $(target)
	rm -f $(objects)

