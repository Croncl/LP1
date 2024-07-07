# Compilador
CC=g++

# Opções de compilação
CFLAGS=-c -Wall

# Nome do executável
TARGET=programa

# Arquivos fonte
SOURCES=main.cpp gerenciador_astronauta.cpp gerenciador_voo.cpp astronauta.cpp voo.cpp menu.cpp

# Objetos
OBJECTS=$(SOURCES:.cpp=.o)

# Bibliotecas (se necessário)
LIBS=

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
