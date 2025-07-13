# Define o compilador a ser usado (gcc ou clang)
CC = gcc

# Flags do compilador: -Wall (mostra todos os avisos), -g (inclui infos de debug)
CFLAGS = -Wall -g

# Nome do programa executável final
TARGET = cinema_cli

# Lista de todos os arquivos de código-fonte (.c)
SOURCES = Main.c Cinema_i.c

# Gera a lista de arquivos de objeto (.o) a partir dos fontes
OBJECTS = $(SOURCES:.c=.o)

# Regra principal: para criar o executável, primeiro crie os arquivos de objeto
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "🔗 Ligando os arquivos para criar o executável..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✅ Programa '$(TARGET)' criado com sucesso!"

# Regra genérica para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra "clean" para limpar os arquivos gerados
clean:
	@echo "🧹 Limpando arquivos compilados..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Limpeza concluída."