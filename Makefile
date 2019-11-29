# ====================================================
# >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
# ====================================================

LINK.o = $(LINK.cc)
CXXFLAGS = -Wall -Wextra -I Headers #-Werror
#LDLIBS

# Nome do executável (contém a main)
EXEC = escalona
# Arquivos que serão compilados (sem a extensão)
ARQUIVOS =	$(EXEC)				\
			SerializabilityResolver	\
			Transactions

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
