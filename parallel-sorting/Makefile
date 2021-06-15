# source files.
SRC = sortComparison.c

OBJ = $(SRC:.cpp=.o)

OUT = sort

# include directories
INCLUDES = -I. 
 
# C compiler flags 
CCFLAGS = -fopenmp -std=c99 -O3 -g -Wall 

# compiler
CCC = gcc

# libraries
LIBS = 

.SUFFIXES: .cpp .c 


default: $(OUT)

.cpp.o:
	$(CCC) $(CCFLAGS) $(INCLUDES)  -c $< -o $@

.c.o:
	$(CCC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

$(OUT): $(OBJ)
	$(CCC) -o $(OUT) $(CCFLAGS) $(OBJ) $(LIBS) 

depend:  dep
#
#dep:
#	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC)

clean:
	rm -f *.o .a *~ Makefile.bak $(OUT)
