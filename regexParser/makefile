CXX = g++

CXXFLAGS = -g

EXEC = a.out
SRCS = $(wildcard *.cpp parser/*.cpp fragment/*.cpp state/*.cpp automata/*.cpp)

OBJS = $(SRCS:.cpp=.o)

RM = rm -f

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJS)
	@echo "Ligando os arquivos objeto para criar o executável: $(EXEC)"
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
	@echo "Compilação concluída com sucesso!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: $(EXEC)
	@echo "Executando o programa..."
	./$(EXEC)

.PHONY: clean
clean:
	@echo "Limpando arquivos gerados..."
	$(RM) $(OBJS) $(EXEC)
	@echo "Limpeza concluída."
