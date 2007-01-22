SRC	= Main.C Chain.C Experiment.C Lock.C Output.C Run.C SpinBarrier.C Timer.C Thread.C Types.C

#
# BIT  = { 32 | 64 }
# MODE = { NUMA | SMP }
#
BIT	= 64
# MODE	= NUMA
MODE	= SMP
# LIB	= -lpthread -lnuma
LIB	= -lpthread

HDR	= $(SRC:.C=.h)
OBJ	= $(SRC:.C=.o)
EXE	= pChase$(BIT)_$(MODE)

RM	= /bin/rm
MV	= /bin/mv

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
