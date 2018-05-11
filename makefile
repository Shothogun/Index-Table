IDIR = ../include
CXX = g++  
CXXFLAGS = -I$(IDIR) -std=gnu++11 -g -pedantic -W -Wall -ftest-coverage -fprofile-arcs 
 
ODIR= obj
LDIR =../libs
 
_DEPS = arvore.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
 
_OBJ = Jogo_20_perguntas.o arvore.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
 
$(ODIR)/%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

Jogo_20_perguntas: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean
 
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~s