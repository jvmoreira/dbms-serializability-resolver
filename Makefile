# ====================================================
# >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
# >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
# ====================================================

LINK.o = $(LINK.cc)
CXXFLAGS = -Wall -I Headers -Wextra -Werror
#LDLIBS

# Nome do executável (contém a main)
EXEC = escalona
# Arquivos que serão compilados (sem a extensão)
ARQUIVOS =	$(EXEC)				\
			Operation			\
			SerializabilityResolver	\
			Tester 	\
			Graph

#Arquivos .o
OBJETOS = $(addsuffix .o, $(ARQUIVOS))

.PHONY : all clean

all: $(EXEC)

# Executável depende dos objetos
$(EXEC): $(OBJETOS)

test: all
	./$(EXEC) < Transactions/transactionRequest.txt
#./$(EXEC) < Transactions/transactionRequest.txt > Transactions/schedule.txt
#diff Transactions/schedule.txt Transactions/expectedSchedule.txt

# Remoção de objetos e executável
clean:
	-rm -f *.o
purge: clean
	-rm -f $(EXEC)
