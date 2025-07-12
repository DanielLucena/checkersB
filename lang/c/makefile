# O nome do compilador
CC = gcc
# O nome do executável final
EXECUTABLE = Main

# A regra padrão (o que acontece quando você digita apenas 'make')
all: $(EXECUTABLE)

# Regra para criar o executável a partir do arquivo-objeto
$(EXECUTABLE): Main.o
	$(CC) Main.o -o $(EXECUTABLE)

# Regra para criar o arquivo-objeto a partir do arquivo .c
Main.o: Main.c
	$(CC) -c Main.c

# Regra para executar o programa (use 'make run')
run: all
	./$(EXECUTABLE)

# Regra para limpar os arquivos gerados (use 'make clean')
clean:
	rm -f Main.o $(EXECUTABLE)