# MODE=NUMA make -j

#
# BIT  = { 32 | 64 }
# MODE = { NUMA | SMP }
#
# BIT	= 64
# MODE	= NUMA
# MODE	= SMP

ifneq ($(BIT), 64)
ifneq ($(BIT), 32)
BIT	= 64
endif
endif

ifneq ($(MODE), NUMA)
ifneq ($(MODE), SMP)
MODE	= SMP
endif
endif

ifeq ($(MODE), NUMA)
LIB	= -lpthread -lnuma
endif

ifeq ($(MODE), SMP)
LIB	= -lpthread
endif

SRC	= Main.C Chain.C Experiment.C Lock.C Output.C Run.C SpinBarrier.C Timer.C Thread.C Types.C
HDR	= $(SRC:.C=.h)
OBJ	= $(SRC:.C=.o)
EXE	= pChase$(BIT)_$(MODE)

RM	= /bin/rm
MV	= /bin/mv
CI	= /usr/bin/ci
CO	= /usr/bin/co

CXXFLAGS= -O3 -m$(BIT) -D$(MODE)

.C.o:
	$(CXX) -c $(CXXFLAGS) $<

$(EXE):	$(OBJ)
	$(CXX) -o $(EXE) $(CXXFLAGS) $(OBJ) $(LIB)

$(OBJ):	$(HDR)

rmexe:
	$(RM) -rf $(EXE)

rmobj:
	$(RM) -rf $(OBJ)

ci:
	$(CI) -f $(SRC) $(HDR) Makefile

co:
	$(CO) -l $(SRC) $(HDR) Makefile
